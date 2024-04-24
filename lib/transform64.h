#pragma once

#include <immintrin.h>
#include <cmath>
#include <algorithm>

namespace DoubleGeometry {

struct Point {
    double x;
    double y;
};

struct PackedPoint {
    alignas(32)
    double x[4];
    alignas(32)
    double y[4];

    PackedPoint() = default;

    PackedPoint(const double* in_x, const double* in_y) {
        std::copy(in_x, in_x + 4, x);
        std::copy(in_y, in_y + 4, y);
    }

    PackedPoint(const double* source) {
        std::copy(source, source + 4, x);
        std::copy(source + 4, source + 8, y);
    }
};

struct PackedSegment {
    PackedPoint start;
    PackedPoint finish;

    PackedSegment() = default;

    PackedSegment(const PackedPoint& point1, const PackedPoint& point2) {
        start = {point1.x, point1.y};
        finish = {point2.x, point2.y};
    }
};

struct DoubleDirection {
    double cos;
    double sin;

    DoubleDirection(double in_cos, double in_sin) : cos(in_cos), sin(in_sin) {}

    DoubleDirection(double angle) : cos(std::cos(angle)), sin(std::sin(angle)) {}
};

using RadianAngle = double;

// Points
extern "C" PackedPoint Translate_asm(const PackedPoint& p, Point delta);

inline PackedPoint Translate_imm(const PackedPoint& p, Point delta) {
    const auto x_new = _mm256_add_pd(_mm256_load_pd(p.x), _mm256_set1_pd(delta.x));
    const auto y_new = _mm256_add_pd(_mm256_load_pd(p.y), _mm256_set1_pd(delta.y));
    PackedPoint res;
    _mm256_store_pd(res.x, x_new);
    _mm256_store_pd(res.y, y_new);
    return res;
}

inline PackedPoint Translate_cpp(const PackedPoint& p, Point delta) {
    PackedPoint res;
    for (int i = 0; i < 4; i++) {
        res.x[i] = p.x[i] + delta.x;
        res.y[i] = p.y[i] + delta.y;
    }
    return res;
}

extern "C" PackedPoint Rotate_asm(const PackedPoint& p, DoubleDirection dir);

inline PackedPoint Rotate_asm(const PackedPoint& p, RadianAngle angle) {
    return Rotate_asm(p, DoubleDirection(angle));
}

inline PackedPoint Rotate_imm(const PackedPoint& p, RadianAngle angle) {
    const DoubleDirection dir(angle);
    const auto packed_cos = _mm256_set1_pd(dir.cos);
    const auto packed_sin = _mm256_set1_pd(dir.sin);

    const auto x = _mm256_load_pd(p.x);
    const auto y = _mm256_load_pd(p.y);
    const auto x_new = _mm256_fmsub_pd(x, packed_cos, _mm256_mul_pd(y, packed_sin)); // x = x*cos - y*sin
    const auto y_new = _mm256_fmadd_pd(x, packed_sin, _mm256_mul_pd(y, packed_cos)); // y = x*sin + y*cos
    PackedPoint result;
    _mm256_store_pd(result.x, x_new);
    _mm256_store_pd(result.y, y_new);
    return result;
}

inline PackedPoint Rotate_cpp(const PackedPoint& p, RadianAngle angle) {
    const DoubleDirection dir(angle);
    PackedPoint result;
    for (int i = 0; i < 4; i++) {
        const Point mem{p.x[i], p.y[i]};
        result.x[i] = mem.x * dir.cos - mem.y * dir.sin;
        result.y[i] = mem.x * dir.sin + mem.y * dir.cos;
    }
    return result;
}

// Segment
inline PackedSegment Translate_imm(const PackedSegment& s, Point delta) {
    const auto packed_dx = _mm256_set1_pd(delta.x);
    const auto packed_dy = _mm256_set1_pd(delta.y);
    PackedSegment res;
    _mm256_store_pd(res.start.x, _mm256_add_pd(_mm256_load_pd(s.start.x), packed_dx));
    _mm256_store_pd(res.start.y, _mm256_add_pd(_mm256_load_pd(s.start.y), packed_dy));
    _mm256_store_pd(res.finish.x, _mm256_add_pd(_mm256_load_pd(s.finish.x), packed_dx));
    _mm256_store_pd(res.finish.y, _mm256_add_pd(_mm256_load_pd(s.finish.y), packed_dy));
    return res;
}

inline PackedSegment Translate_cpp(const PackedSegment& s, Point delta) {
    PackedSegment res;
    res.start = Translate_cpp(s.start, delta);
    res.finish = Translate_cpp(s.finish, delta);
    return res;
}

inline PackedSegment Rotate_imm(const PackedSegment& s, RadianAngle angle) {
    const DoubleDirection dir(angle);
    const auto packed_cos = _mm256_set1_pd(dir.cos);
    const auto packed_sin = _mm256_set1_pd(dir.sin);

    const auto x1 = _mm256_load_pd(s.start.x);
    const auto y1 = _mm256_load_pd(s.start.y);
    const auto x2 = _mm256_load_pd(s.finish.x);
    const auto y2 = _mm256_load_pd(s.finish.y);
    PackedSegment res;
    _mm256_store_pd(res.start.x, _mm256_fmsub_pd(x1, packed_cos, _mm256_mul_pd(y1, packed_sin))); // x1 = x1*cos - y1*sin
    _mm256_store_pd(res.start.y, _mm256_fmadd_pd(x1, packed_sin, _mm256_mul_pd(y1, packed_cos))); // y1 = x1*sin + y1*cos
    _mm256_store_pd(res.finish.x, _mm256_fmsub_pd(x2, packed_cos, _mm256_mul_pd(y2, packed_sin))); // x2 = x2*cos - y2*sin
    _mm256_store_pd(res.finish.y, _mm256_fmadd_pd(x2, packed_sin, _mm256_mul_pd(y2, packed_cos))); // y2 = x2*sin + y2*cos
    return res;
}

inline PackedSegment Rotate_cpp(const PackedSegment& s, RadianAngle angle) {
    PackedSegment res;
    res.start = Rotate_cpp(s.start, angle);
    res.finish = Rotate_cpp(s.finish, angle);
    return res;
}
}
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
    PackedPoint res;
    const auto x_new = _mm256_add_pd(_mm256_load_pd(p.x), _mm256_set1_pd(delta.x));
    const auto y_new = _mm256_add_pd(_mm256_load_pd(p.y), _mm256_set1_pd(delta.y));
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
    const auto x_new = _mm256_fmsub_pd(x, packed_cos, _mm256_mul_pd(y, packed_sin)); // xcos - ysin
    const auto y_new = _mm256_fmadd_pd(x, packed_sin, _mm256_mul_pd(y, packed_cos)); // xsin + ycos
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
/*
inline void TranslateS64_imm(PackedSegment* s, Point delta) {
    auto packed_dx = _mm256_set1_pd(delta.x);
    auto packed_dy = _mm256_set1_pd(delta.y);
    _mm256_store_pd(s->start.x, _mm256_add_pd(_mm256_load_pd(s->start.x), packed_dx));
    _mm256_store_pd(s->start.y, _mm256_add_pd(_mm256_load_pd(s->start.y), packed_dy));
    _mm256_store_pd(s->end.x, _mm256_add_pd(_mm256_load_pd(s->end.x), packed_dx));
    _mm256_store_pd(s->end.y, _mm256_add_pd(_mm256_load_pd(s->end.y), packed_dy));
}

inline void RotateS64_imm(PackedSegment* s, double angle) {
    double sin = std::sin(angle);
    double cos = std::cos(angle);
    auto pcos = _mm256_set1_pd(cos);
    auto psin = _mm256_set1_pd(sin);

    auto x1 = _mm256_load_pd(s->start.x);
    auto y1 = _mm256_load_pd(s->start.y);
    auto x2 = _mm256_load_pd(s->end.x);
    auto y2 = _mm256_load_pd(s->end.y);
    _mm256_store_pd(s->start.x, _mm256_fmsub_pd(x1, pcos, _mm256_mul_pd(y1, psin))); // xcos - ysin
    _mm256_store_pd(s->start.y, _mm256_fmadd_pd(x1, psin, _mm256_mul_pd(y1, pcos))); // xsin + ycos
    _mm256_store_pd(s->end.x, _mm256_fmsub_pd(x2, pcos, _mm256_mul_pd(y2, psin))); // xcos - ysin
    _mm256_store_pd(s->end.y, _mm256_fmadd_pd(x2, psin, _mm256_mul_pd(y2, pcos))); // xsin + ycos
}

inline void TranslateS64_cpp(PackedSegment* s, Point delta) {
    for (int i = 0; i < 4; i++) {
        s->start.x[i] += delta.x;
        s->start.y[i] += delta.y;
        s->end.x[i] += delta.x;
        s->end.y[i] += delta.y;
    }
}

inline void RotateS64_cpp(PackedSegment* s, double angle) {
    double sin = std::sin(angle);
    double cos = std::cos(angle);
    for (int i = 0; i < 4; i++) {
        auto x1 = s->start.x[i];
        auto y1 = s->start.y[i];
        auto x2 = s->end.x[i];
        auto y2 = s->end.y[i];
        s->start.x[i] = x1 * cos - y1 * sin;
        s->start.y[i] = x1 * sin + y1 * cos;
        s->end.x[i] = x2 * cos - y2 * sin;
        s->end.y[i] = x2 * sin + y2 * cos;
    }
}
*/
}
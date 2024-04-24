#pragma once

#include <immintrin.h>
#include <cmath>
#include <algorithm>

/// float precision points and segments transformations
namespace SingleGeometry {

struct Point {
    float x;
    float y;
};

/// 4 float precision points
struct PackedPoint {
    alignas(32)
    float x[8];
    alignas(32)
    float y[8];

    PackedPoint() = default;

    PackedPoint(const float* in_x, const float* in_y) {
        std::copy(in_x, in_x + 8, x);
        std::copy(in_y, in_y + 8, y);
    }

    PackedPoint(const float* source) {
        std::copy(source, source + 8, x);
        std::copy(source + 8, source + 16, y);
    }
};

/// 4 float precision segments
struct PackedSegment {
    PackedPoint start;
    PackedPoint finish;
};

using RadianAngle = float;

/// normalized direction vector
struct floatDirection {
    float cos;
    float sin;

    floatDirection(float in_cos, float in_sin) : cos(in_cos), sin(in_sin) {}

    floatDirection(RadianAngle angle) : cos(std::cos(angle)), sin(std::sin(angle)) {}
};

// Points
//extern "C" PackedPoint Translate_asm(const PackedPoint& p, Point delta);

inline PackedPoint Translate_imm(const PackedPoint& p, Point delta) {
    const auto x_new = _mm256_add_ps(_mm256_load_ps(p.x), _mm256_set1_ps(delta.x));
    const auto y_new = _mm256_add_ps(_mm256_load_ps(p.y), _mm256_set1_ps(delta.y));
    PackedPoint res;
    _mm256_store_ps(res.x, x_new);
    _mm256_store_ps(res.y, y_new);
    return res;
}

inline PackedPoint Translate_cpp(const PackedPoint& p, Point delta) {
    PackedPoint res;
    for (int i = 0; i < 8; i++) {
        res.x[i] = p.x[i] + delta.x;
        res.y[i] = p.y[i] + delta.y;
    }
    return res;
}

//extern "C" PackedPoint Rotate_asm(const PackedPoint& p, floatDirection dir);
//
//inline PackedPoint Rotate_asm(const PackedPoint& p, RadianAngle angle) {
//    return Rotate_asm(p, floatDirection(angle));
//}

inline PackedPoint Rotate_imm(const PackedPoint& p, ///< Rotatable points
                              RadianAngle angle ///< Counterclockwise rotation angle
                              ) {
    const floatDirection dir(angle);
    const auto packed_cos = _mm256_set1_ps(dir.cos);
    const auto packed_sin = _mm256_set1_ps(dir.sin);

    const auto x = _mm256_load_ps(p.x);
    const auto y = _mm256_load_ps(p.y);
    const auto x_new = _mm256_fmsub_ps(x, packed_cos, _mm256_mul_ps(y, packed_sin)); // x = x*cos - y*sin
    const auto y_new = _mm256_fmadd_ps(x, packed_sin, _mm256_mul_ps(y, packed_cos)); // y = x*sin + y*cos
    PackedPoint result;
    _mm256_store_ps(result.x, x_new);
    _mm256_store_ps(result.y, y_new);
    return result;
}

inline PackedPoint Rotate_cpp(const PackedPoint& p, RadianAngle angle) {
    const floatDirection dir(angle);
    PackedPoint result;
    for (int i = 0; i < 8; i++) {
        const Point mem{p.x[i], p.y[i]};
        result.x[i] = mem.x * dir.cos - mem.y * dir.sin;
        result.y[i] = mem.x * dir.sin + mem.y * dir.cos;
    }
    return result;
}

// Segment
inline PackedSegment Translate_imm(const PackedSegment& s, ///< Translatable segments
                                   Point delta ///< Offset
                                   ) {
    const auto packed_dx = _mm256_set1_ps(delta.x);
    const auto packed_dy = _mm256_set1_ps(delta.y);
    PackedSegment res;
    _mm256_store_ps(res.start.x, _mm256_add_ps(_mm256_load_ps(s.start.x), packed_dx));
    _mm256_store_ps(res.start.y, _mm256_add_ps(_mm256_load_ps(s.start.y), packed_dy));
    _mm256_store_ps(res.finish.x, _mm256_add_ps(_mm256_load_ps(s.finish.x), packed_dx));
    _mm256_store_ps(res.finish.y, _mm256_add_ps(_mm256_load_ps(s.finish.y), packed_dy));
    return res;
}

inline PackedSegment Translate_cpp(const PackedSegment& s, Point delta) {
    PackedSegment res;
    res.start = Translate_cpp(s.start, delta);
    res.finish = Translate_cpp(s.finish, delta);
    return res;
}

inline PackedSegment Rotate_imm(const PackedSegment& s, ///< Rotatable segments
                                RadianAngle angle ///< Counterclockwise rotation angle
                                ) {
    const floatDirection dir(angle);
    const auto packed_cos = _mm256_set1_ps(dir.cos);
    const auto packed_sin = _mm256_set1_ps(dir.sin);

    const auto x1 = _mm256_load_ps(s.start.x);
    const auto y1 = _mm256_load_ps(s.start.y);
    const auto x2 = _mm256_load_ps(s.finish.x);
    const auto y2 = _mm256_load_ps(s.finish.y);
    PackedSegment res;
    _mm256_store_ps(res.start.x, _mm256_fmsub_ps(x1, packed_cos, _mm256_mul_ps(y1, packed_sin))); // x1 = x1*cos - y1*sin
    _mm256_store_ps(res.start.y, _mm256_fmadd_ps(x1, packed_sin, _mm256_mul_ps(y1, packed_cos))); // y1 = x1*sin + y1*cos
    _mm256_store_ps(res.finish.x, _mm256_fmsub_ps(x2, packed_cos, _mm256_mul_ps(y2, packed_sin))); // x2 = x2*cos - y2*sin
    _mm256_store_ps(res.finish.y, _mm256_fmadd_ps(x2, packed_sin, _mm256_mul_ps(y2, packed_cos))); // y2 = x2*sin + y2*cos
    return res;
}

inline PackedSegment Rotate_cpp(const PackedSegment& s, RadianAngle angle) {
    PackedSegment res;
    res.start = Rotate_cpp(s.start, angle);
    res.finish = Rotate_cpp(s.finish, angle);
    return res;
}
}
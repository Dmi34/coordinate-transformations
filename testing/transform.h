#pragma once

#include <algorithm>
#include <cmath>
#include <immintrin.h>

/// Transformations of points and segments with double-precision floating-point coordinates
namespace DoubleGeometry {

//------------------------------------------------------------------------------
// Geometric structures
//------------------------------------------------------------------------------

struct Point {
    double x;
    double y;
};

/// Four packed points
struct PackedPoint {
    alignas(32)
    double x[4];
    alignas(32)
    double y[4];

    PackedPoint() = default;

    /// @param [in] in_x - The beginning of x-coordinate range
    /// @param [in] in_y - The beginning of y-coordinate range
    PackedPoint(const double* in_x, const double* in_y) {
        std::copy(in_x, in_x + 4, x);
        std::copy(in_y, in_y + 4, y);
    }
};

/// Four packed segments (two packed points)
struct PackedSegment {
    PackedPoint start;
    PackedPoint finish;
};

using RadianAngle = double;

/// Unit vector (normalized direction)
struct Direction {
    double cos;
    double sin;

    Direction(double in_cos, double in_sin) : cos(in_cos), sin(in_sin) {}

    /// @param [in] angle - Angle between Ox and the vector
    Direction(RadianAngle angle) : cos(std::cos(angle)), sin(std::sin(angle)) {}
};

//------------------------------------------------------------------------------
// Points transformations
//------------------------------------------------------------------------------

extern "C" void TranslateDoublePointAsm(const PackedPoint* dest, const PackedPoint& p, Point delta);

/// @param [in] p - Translatable packed point
/// @param [in] delta - Offset
/// @returns Translated packed point
inline PackedPoint TranslateAsm(const PackedPoint& p, Point delta) {
    PackedPoint result;
    TranslateDoublePointAsm(&result, p, delta);
    return result;
}

/// @param [in] p - Translatable packed point
/// @param [in] delta - Offset
/// @returns Translated packed point
inline PackedPoint TranslateImm(const PackedPoint& p, Point delta) {
    const auto x_new = _mm256_add_pd(_mm256_load_pd(p.x), _mm256_set1_pd(delta.x));
    const auto y_new = _mm256_add_pd(_mm256_load_pd(p.y), _mm256_set1_pd(delta.y));
    PackedPoint res;
    _mm256_store_pd(res.x, x_new);
    _mm256_store_pd(res.y, y_new);
    return res;
}

/// @param [in] p - Translatable packed point
/// @param [in] delta - Offset
/// @returns Translated packed point
inline PackedPoint TranslateCpp(const PackedPoint& p, Point delta) {
    PackedPoint res;
    for (int i = 0; i < 4; i++) {
        res.x[i] = p.x[i] + delta.x;
        res.y[i] = p.y[i] + delta.y;
    }
    return res;
}

extern "C" void RotateDoublePointAsm(const PackedPoint* dest, const PackedPoint& p, Direction dir);

/// @param [in] p - Rotatable packed point
/// @param [in] angle - Rotation angle
/// @returns Rotated packed point
inline PackedPoint RotateAsm(const PackedPoint& p, RadianAngle angle) {
    PackedPoint result;
    RotateDoublePointAsm(&result, p, Direction(angle));
    return result;
}

/// @param [in] p - Rotatable packed point
/// @param [in] angle - Rotation angle
/// @returns Rotated packed point
inline PackedPoint RotateImm(const PackedPoint& p, RadianAngle angle) {
    const Direction dir(angle);
    const auto packed_cos = _mm256_set1_pd(dir.cos);
    const auto packed_sin = _mm256_set1_pd(dir.sin);

    const auto x = _mm256_load_pd(p.x);
    const auto y = _mm256_load_pd(p.y);
    // x = x*cos - y*sin
    // y = x*sin + y*cos
    const auto x_new = _mm256_fmsub_pd(x, packed_cos, _mm256_mul_pd(y, packed_sin));
    const auto y_new = _mm256_fmadd_pd(x, packed_sin, _mm256_mul_pd(y, packed_cos));
    PackedPoint result;
    _mm256_store_pd(result.x, x_new);
    _mm256_store_pd(result.y, y_new);
    return result;
}

/// @param [in] p - Rotatable packed point
/// @param [in] angle - Rotation angle
/// @returns Rotated packed point
inline PackedPoint RotateCpp(const PackedPoint& p, RadianAngle angle) {
    const Direction dir(angle);
    PackedPoint result;
    for (int i = 0; i < 4; i++) {
        const Point mem{p.x[i], p.y[i]};
        result.x[i] = mem.x * dir.cos - mem.y * dir.sin;
        result.y[i] = mem.x * dir.sin + mem.y * dir.cos;
    }
    return result;
}

//------------------------------------------------------------------------------
// Segments transformations
//------------------------------------------------------------------------------

extern "C" void TranslateDoubleSegmentAsm(const PackedSegment* dest, const PackedSegment& s, Point delta);

/// @param [in] s - Translatable packed segment
/// @param [in] delta - Offset
/// @returns Translated packed segment
inline PackedSegment TranslateAsm(const PackedSegment& s, Point delta) {
    PackedSegment result;
    TranslateDoubleSegmentAsm(&result, s, delta);
    return result;
}

/// @param [in] s - Translatable packed segment
/// @param [in] delta - Offset
/// @returns Translated packed segment
inline PackedSegment TranslateImm(const PackedSegment& s, Point delta) {
    const auto packed_dx = _mm256_set1_pd(delta.x);
    const auto packed_dy = _mm256_set1_pd(delta.y);
    PackedSegment res;
    _mm256_store_pd(res.start.x, _mm256_add_pd(_mm256_load_pd(s.start.x), packed_dx));
    _mm256_store_pd(res.start.y, _mm256_add_pd(_mm256_load_pd(s.start.y), packed_dy));
    _mm256_store_pd(res.finish.x, _mm256_add_pd(_mm256_load_pd(s.finish.x), packed_dx));
    _mm256_store_pd(res.finish.y, _mm256_add_pd(_mm256_load_pd(s.finish.y), packed_dy));
    return res;
}

/// @param [in] s - Translatable packed segment
/// @param [in] delta - Offset
/// @returns Translated packed segment
inline PackedSegment TranslateCpp(const PackedSegment& s, Point delta) {
    PackedSegment res;
    res.start = TranslateCpp(s.start, delta);
    res.finish = TranslateCpp(s.finish, delta);
    return res;
}

extern "C" void RotateDoubleSegmentAsm(const PackedSegment* dest, const PackedSegment& s, Direction dir);

/// @param [in] s - Rotatable packed segment
/// @param [in] angle - Rotation angle
/// @returns Rotated packed segment
inline PackedSegment RotateAsm(const PackedSegment& s, RadianAngle angle) {
    PackedSegment result;
    RotateDoubleSegmentAsm(&result, s, Direction(angle));
    return result;
}

/// @param [in] s - Rotatable packed segment
/// @param [in] angle - Rotation angle
/// @returns Rotated packed segment
inline PackedSegment RotateImm(const PackedSegment& s, RadianAngle angle) {
    const Direction dir(angle);
    const auto packed_cos = _mm256_set1_pd(dir.cos);
    const auto packed_sin = _mm256_set1_pd(dir.sin);

    const auto x1 = _mm256_load_pd(s.start.x);
    const auto y1 = _mm256_load_pd(s.start.y);
    const auto x2 = _mm256_load_pd(s.finish.x);
    const auto y2 = _mm256_load_pd(s.finish.y);
    PackedSegment res;
    // x = x*cos - y*sin
    // y = x*sin + y*cos
    _mm256_store_pd(res.start.x, _mm256_fmsub_pd(x1, packed_cos, _mm256_mul_pd(y1, packed_sin)));
    _mm256_store_pd(res.start.y, _mm256_fmadd_pd(x1, packed_sin, _mm256_mul_pd(y1, packed_cos)));
    _mm256_store_pd(res.finish.x, _mm256_fmsub_pd(x2, packed_cos, _mm256_mul_pd(y2, packed_sin)));
    _mm256_store_pd(res.finish.y, _mm256_fmadd_pd(x2, packed_sin, _mm256_mul_pd(y2, packed_cos)));
    return res;
}

/// @param [in] s - Rotatable packed segment
/// @param [in] angle - Rotation angle
/// @returns Rotated packed segment
inline PackedSegment RotateCpp(const PackedSegment& s, RadianAngle angle) {
    PackedSegment res;
    res.start = RotateCpp(s.start, angle);
    res.finish = RotateCpp(s.finish, angle);
    return res;
}

}



/// Transformations of points and segments with single-precision floating-point coordinates
namespace SingleGeometry {

//------------------------------------------------------------------------------
// Geometric structures
//------------------------------------------------------------------------------

struct Point {
    float x;
    float y;
};

/// Eight packed points
struct PackedPoint {
    alignas(32)
    float x[8];
    alignas(32)
    float y[8];

    PackedPoint() = default;

    /// @param [in] in_x - The beginning of x-coordinate range
    /// @param [in] in_y - The beginning of y-coordinate range
    PackedPoint(const float* in_x, const float* in_y) {
        std::copy(in_x, in_x + 8, x);
        std::copy(in_y, in_y + 8, y);
    }
};

/// Eight packed segments (two packed points)
struct PackedSegment {
    PackedPoint start;
    PackedPoint finish;
};

using RadianAngle = float;

/// Unit vector (normalized direction)
struct Direction {
    float cos;
    float sin;

    Direction(float in_cos, float in_sin) : cos(in_cos), sin(in_sin) {}

    /// @param [in] angle - Angle between Ox and the vector
    Direction(RadianAngle angle) : cos(std::cos(angle)), sin(std::sin(angle)) {}
};

//------------------------------------------------------------------------------
// Points transformations
//------------------------------------------------------------------------------

extern "C" void TranslateSinglePointAsm(const PackedPoint* dest, const PackedPoint& p, Point delta);

/// @param [in] p - Translatable packed point
/// @param [in] delta - Offset
/// @returns Translated packed point
inline PackedPoint TranslateAsm(const PackedPoint& p, Point delta) {
    PackedPoint result;
    TranslateSinglePointAsm(&result, p, delta);
    return result;
}

/// @param [in] p - Translatable packed point
/// @param [in] delta - Offset
/// @returns Translated packed point
inline PackedPoint TranslateImm(const PackedPoint& p, Point delta) {
    const auto x_new = _mm256_add_ps(_mm256_load_ps(p.x), _mm256_set1_ps(delta.x));
    const auto y_new = _mm256_add_ps(_mm256_load_ps(p.y), _mm256_set1_ps(delta.y));
    PackedPoint res;
    _mm256_store_ps(res.x, x_new);
    _mm256_store_ps(res.y, y_new);
    return res;
}

/// @param [in] p - Translatable packed point
/// @param [in] delta - Offset
/// @returns Translated packed point
inline PackedPoint TranslateCpp(const PackedPoint& p, Point delta) {
    PackedPoint res;
    for (int i = 0; i < 8; i++) {
        res.x[i] = p.x[i] + delta.x;
        res.y[i] = p.y[i] + delta.y;
    }
    return res;
}

extern "C" void RotateSinglePointAsm(const PackedPoint* dest, const PackedPoint& p, Direction dir);

/// @param [in] p - Rotatable packed point
/// @param [in] angle - Rotation angle
/// @returns Rotated packed point
inline PackedPoint RotateAsm(const PackedPoint& p, RadianAngle angle) {
    PackedPoint result;
    RotateSinglePointAsm(&result, p, Direction(angle));
    return result;
}

/// @param [in] p - Rotatable packed point
/// @param [in] angle - Rotation angle
/// @returns Rotated packed point
inline PackedPoint RotateImm(const PackedPoint& p, RadianAngle angle) {
    const Direction dir(angle);
    const auto packed_cos = _mm256_set1_ps(dir.cos);
    const auto packed_sin = _mm256_set1_ps(dir.sin);

    const auto x = _mm256_load_ps(p.x);
    const auto y = _mm256_load_ps(p.y);
    // x = x*cos - y*sin
    // y = x*sin + y*cos
    const auto x_new = _mm256_fmsub_ps(x, packed_cos, _mm256_mul_ps(y, packed_sin));
    const auto y_new = _mm256_fmadd_ps(x, packed_sin, _mm256_mul_ps(y, packed_cos));
    PackedPoint result;
    _mm256_store_ps(result.x, x_new);
    _mm256_store_ps(result.y, y_new);
    return result;
}

/// @param [in] p - Rotatable packed point
/// @param [in] angle - Rotation angle
/// @returns Rotated packed point
inline PackedPoint RotateCpp(const PackedPoint& p, RadianAngle angle) {
    const Direction dir(angle);
    PackedPoint result;
    for (int i = 0; i < 8; i++) {
        const Point mem{p.x[i], p.y[i]};
        result.x[i] = mem.x * dir.cos - mem.y * dir.sin;
        result.y[i] = mem.x * dir.sin + mem.y * dir.cos;
    }
    return result;
}

//------------------------------------------------------------------------------
// Segments transformations
//------------------------------------------------------------------------------

extern "C" void TranslateSingleSegmentAsm(const PackedSegment* dest, const PackedSegment& s, Point delta);

/// @param [in] s - Translatable packed segment
/// @param [in] delta - Offset
/// @returns Translated packed segment
inline PackedSegment TranslateAsm(const PackedSegment& s, Point delta) {
    PackedSegment result;
    TranslateSingleSegmentAsm(&result, s, delta);
    return result;
}

/// @param [in] s - Translatable packed segment
/// @param [in] delta - Offset
/// @returns Translated packed segment
inline PackedSegment TranslateImm(const PackedSegment& s, Point delta) {
    const auto packed_dx = _mm256_set1_ps(delta.x);
    const auto packed_dy = _mm256_set1_ps(delta.y);
    PackedSegment res;
    _mm256_store_ps(res.start.x, _mm256_add_ps(_mm256_load_ps(s.start.x), packed_dx));
    _mm256_store_ps(res.start.y, _mm256_add_ps(_mm256_load_ps(s.start.y), packed_dy));
    _mm256_store_ps(res.finish.x, _mm256_add_ps(_mm256_load_ps(s.finish.x), packed_dx));
    _mm256_store_ps(res.finish.y, _mm256_add_ps(_mm256_load_ps(s.finish.y), packed_dy));
    return res;
}

/// @param [in] s - Translatable packed segment
/// @param [in] delta - Offset
/// @returns Translated packed segment
inline PackedSegment TranslateCpp(const PackedSegment& s, Point delta) {
    PackedSegment res;
    res.start = TranslateCpp(s.start, delta);
    res.finish = TranslateCpp(s.finish, delta);
    return res;
}

extern "C" void RotateSingleSegmentAsm(const PackedSegment* dest, const PackedSegment& s, Direction dir);

/// @param [in] s - Rotatable packed segment
/// @param [in] angle - Rotation angle
/// @returns Rotated packed segment
inline PackedSegment RotateAsm(const PackedSegment& s, RadianAngle angle) {
    PackedSegment result;
    RotateSingleSegmentAsm(&result, s, Direction(angle));
    return result;
}

/// @param [in] s - Rotatable packed segment
/// @param [in] angle - Rotation angle
/// @returns Rotated packed segment
inline PackedSegment RotateImm(const PackedSegment& s, RadianAngle angle) {
    const Direction dir(angle);
    const auto packed_cos = _mm256_set1_ps(dir.cos);
    const auto packed_sin = _mm256_set1_ps(dir.sin);

    const auto x1 = _mm256_load_ps(s.start.x);
    const auto y1 = _mm256_load_ps(s.start.y);
    const auto x2 = _mm256_load_ps(s.finish.x);
    const auto y2 = _mm256_load_ps(s.finish.y);
    PackedSegment res;
    // x = x*cos - y*sin
    // y = x*sin + y*cos
    _mm256_store_ps(res.start.x, _mm256_fmsub_ps(x1, packed_cos, _mm256_mul_ps(y1, packed_sin)));
    _mm256_store_ps(res.start.y, _mm256_fmadd_ps(x1, packed_sin, _mm256_mul_ps(y1, packed_cos)));
    _mm256_store_ps(res.finish.x, _mm256_fmsub_ps(x2, packed_cos, _mm256_mul_ps(y2, packed_sin)));
    _mm256_store_ps(res.finish.y, _mm256_fmadd_ps(x2, packed_sin, _mm256_mul_ps(y2, packed_cos)));
    return res;
}

/// @param [in] s - Rotatable packed segment
/// @param [in] angle - Rotation angle
/// @returns Rotated packed segment
inline PackedSegment RotateCpp(const PackedSegment& s, RadianAngle angle) {
    PackedSegment res;
    res.start = RotateCpp(s.start, angle);
    res.finish = RotateCpp(s.finish, angle);
    return res;
}

}
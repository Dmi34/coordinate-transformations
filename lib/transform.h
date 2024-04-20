#pragma once

#include <cmath>
#include <immintrin.h>

struct alignas(16) Point {
    double x;
    double y;
};

struct alignas(16) PackedPoint {
    double* x;
    double* y;
};

struct alignas(16) Segment {
    Point start;
    Point end;
};

struct alignas(16) PackedSegment {
    PackedPoint start;
    PackedPoint end;
};

extern "C" void TranslateI64_avx2(PackedPoint* p, Point delta);
extern "C" void RotateI64_avx2(PackedPoint* p, double sin, double cos);

// BAZEL or compiler cannot differentiate ectern "C" and usual function with the same signature. Has to be rewritten to other signature

// void RotateI64_avx2(PackedPoint* p, double angle) {
//     RotateI64_avx2(p, std::sin(angle), std::cos(angle));
// }

void TranslateI64_intrin(PackedPoint* p, Point delta);
//void RotateI64_intrin(PackedPoint* p, double angle);

// INLINING PROBLEM. NOT FIXED.

inline void RotateI64_intrin(PackedPoint* p, double angle) {
    double sin = std::sin(angle);
    double cos = std::cos(angle);
    __m256d pcos = _mm256_set1_pd(cos);
    __m256d psin = _mm256_set1_pd(sin);

    __m256d x = _mm256_load_pd(p->x);
    __m256d y = _mm256_load_pd(p->y);
    __m256d x_new = _mm256_fmsub_pd(x, pcos, _mm256_mul_pd(y, psin)); // xcos - ysin
    __m256d y_new = _mm256_fmadd_pd(x, psin, _mm256_mul_pd(y, pcos)); // xsin + ycos
    _mm256_store_pd(p->x, x_new);
    _mm256_store_pd(p->y, y_new);
}

void TranslateI64(PackedPoint* p, Point delta);
void RotateI64(PackedPoint* p, double angle);


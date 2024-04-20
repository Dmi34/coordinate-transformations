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

extern "C" void TranslateF64_asm(PackedPoint* p, Point delta);
extern "C" void RotateF64_asm(PackedPoint* p, double sin, double cos);

inline void RotateI64_avx2(PackedPoint* p, double angle) {
    RotateF64_asm(p, std::sin(angle), std::cos(angle));
}

inline void TranslateF64_imm(PackedPoint* p, Point delta) {
    auto x_new = _mm256_add_pd(_mm256_load_pd(p->x), _mm256_set1_pd(delta.x));
    auto y_new = _mm256_add_pd(_mm256_load_pd(p->y), _mm256_set1_pd(delta.y));
    _mm256_store_pd(p->x, x_new);
    _mm256_store_pd(p->y, y_new);
}

inline void imm(PackedPoint* p, double angle) {
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

inline void TranslateI64(PackedPoint* p, Point delta) {
    for (int i = 0; i < 4; i++) {
        p->x[i] += delta.x;
        p->y[i] += delta.y;
    }
}

inline void RotateI64(PackedPoint* p, double angle) {
    double sin = std::sin(angle);
    double cos = std::cos(angle);
    for (int i = 0; i < 4; i++) {
        p->x[i] = p->x[i] * cos - p->y[i] * sin;
        p->y[i] = p->x[i] * sin + p->y[i] * cos;
    }
}


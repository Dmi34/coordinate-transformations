#pragma once

#include <immintrin.h>
#include <cmath>
#include <algorithm>

struct Point {
    double x;
    double y;
};

struct PackedPoint {
    //    alignas(32)
    double* x;
    //    alignas(32)
    double* y;

    // PackedPoint(double* _x, double* _y) : x(new alignas(32) double[4]), y(new alignas(32) double[4]) {
    //     std::copy(_x, _x + 4, x);
    //     std::copy(_y, _y + 4, y);
    // }
};

struct Segment {
    Point start;
    Point end;
};

struct PackedSegment {
    PackedPoint start;
    PackedPoint end;
};

extern "C" void TranslateF64_asm(PackedPoint* p, Point delta);
extern "C" void RotateF64_asm(PackedPoint* p, double sin, double cos);

inline void RotateF64_asm(PackedPoint* p, double angle) {
    RotateF64_asm(p, std::sin(angle), std::cos(angle));
}

inline void TranslateF64_imm(PackedPoint* p, Point delta) {
    auto x_new = _mm256_add_pd(_mm256_load_pd(p->x), _mm256_set1_pd(delta.x));
    auto y_new = _mm256_add_pd(_mm256_load_pd(p->y), _mm256_set1_pd(delta.y));
    _mm256_store_pd(p->x, x_new);
    _mm256_store_pd(p->y, y_new);
}

inline void RotateF64_imm(PackedPoint* p, double angle) {
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

inline void TranslateF64_cpp(PackedPoint* p, Point delta) {
    for (int i = 0; i < 4; i++) {
        p->x[i] += delta.x;
        p->y[i] += delta.y;
    }
}

inline void RotateF64_cpp(PackedPoint* p, double angle) {
    double sin = std::sin(angle);
    double cos = std::cos(angle);
    for (int i = 0; i < 4; i++) {
        auto x = p->x[i];
        auto y = p->y[i];
        p->x[i] = x * cos - y * sin;
        p->y[i] = x * sin + y * cos;
    }
}


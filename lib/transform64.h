#pragma once

#include <immintrin.h>
#include <cmath>
#include <algorithm>

struct Point64 {
    double x;
    double y;
};

struct PackedPoint64 {
    double* x;
    double* y;
};

struct PackedSegment64 {
    PackedPoint64 start;
    PackedPoint64 end;
};

extern "C" void TranslateP64_asm(PackedPoint64* p, Point64 delta);
extern "C" void RotateP64_asm(PackedPoint64* p, double sin, double cos);

inline void RotateP64_asm(PackedPoint64* p, double angle) {
    RotateP64_asm(p, std::sin(angle), std::cos(angle));
}

inline void TranslateP64_imm(PackedPoint64* p, Point64 delta) {
    auto x_new = _mm256_add_pd(_mm256_load_pd(p->x), _mm256_set1_pd(delta.x));
    auto y_new = _mm256_add_pd(_mm256_load_pd(p->y), _mm256_set1_pd(delta.y));
    _mm256_store_pd(p->x, x_new);
    _mm256_store_pd(p->y, y_new);
}

inline void RotateP64_imm(PackedPoint64* p, double angle) {
    double sin = std::sin(angle);
    double cos = std::cos(angle);
    auto pcos = _mm256_set1_pd(cos);
    auto psin = _mm256_set1_pd(sin);

    auto x = _mm256_load_pd(p->x);
    auto y = _mm256_load_pd(p->y);
    auto x_new = _mm256_fmsub_pd(x, pcos, _mm256_mul_pd(y, psin)); // xcos - ysin
    auto y_new = _mm256_fmadd_pd(x, psin, _mm256_mul_pd(y, pcos)); // xsin + ycos
    _mm256_store_pd(p->x, x_new);
    _mm256_store_pd(p->y, y_new);
}

inline void TranslateP64_cpp(PackedPoint64* p, Point64 delta) {
    for (int i = 0; i < 4; i++) {
        p->x[i] += delta.x;
        p->y[i] += delta.y;
    }
}

inline void RotateP64_cpp(PackedPoint64* p, double angle) {
    double sin = std::sin(angle);
    double cos = std::cos(angle);
    for (int i = 0; i < 4; i++) {
        auto x = p->x[i];
        auto y = p->y[i];
        p->x[i] = x * cos - y * sin;
        p->y[i] = x * sin + y * cos;
    }
}

inline void TranslateS64_imm(PackedSegment64* s, Point64 delta) {
    auto packed_dx = _mm256_set1_pd(delta.x);
    auto packed_dy = _mm256_set1_pd(delta.y);
    _mm256_store_pd(s->start.x, _mm256_add_pd(_mm256_load_pd(s->start.x), packed_dx));
    _mm256_store_pd(s->start.y, _mm256_add_pd(_mm256_load_pd(s->start.y), packed_dy));
    _mm256_store_pd(s->end.x, _mm256_add_pd(_mm256_load_pd(s->end.x), packed_dx));
    _mm256_store_pd(s->end.y, _mm256_add_pd(_mm256_load_pd(s->end.y), packed_dy));
}

inline void RotateS64_imm(PackedSegment64* s, double angle) {
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

inline void TranslateS64_cpp(PackedSegment64* s, Point64 delta) {
    for (int i = 0; i < 4; i++) {
        s->start.x[i] += delta.x;
        s->start.y[i] += delta.y;
        s->end.x[i] += delta.x;
        s->end.y[i] += delta.y;
    }
}

inline void RotateS64_cpp(PackedSegment64* s, double angle) {
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

#pragma once

#include <immintrin.h>
#include <cmath>
#include <algorithm>

struct Point32 {
    float x;
    float y;
};

struct PackedPoint32 {
    float* x;
    float* y;
};

struct PackedSegment32 {
    PackedPoint32 start;
    PackedPoint32 end;
};

inline void TranslateP32_imm(PackedPoint32* p, Point32 delta) {
    auto x_new = _mm256_add_ps(_mm256_load_ps(p->x), _mm256_set1_ps(delta.x));
    auto y_new = _mm256_add_ps(_mm256_load_ps(p->y), _mm256_set1_ps(delta.y));
    _mm256_store_ps(p->x, x_new);
    _mm256_store_ps(p->y, y_new);
}

inline void RotateP32_imm(PackedPoint32* p, float angle) {
    float sin = std::sin(angle);
    float cos = std::cos(angle);
    auto pcos = _mm256_set1_ps(cos);
    auto psin = _mm256_set1_ps(sin);

    auto x = _mm256_load_ps(p->x);
    auto y = _mm256_load_ps(p->y);
    auto x_new = _mm256_fmsub_ps(x, pcos, _mm256_mul_ps(y, psin)); // xcos - ysin
    auto y_new = _mm256_fmadd_ps(x, psin, _mm256_mul_ps(y, pcos)); // xsin + ycos
    _mm256_store_ps(p->x, x_new);
    _mm256_store_ps(p->y, y_new);
}

inline void TranslateP32_cpp(PackedPoint32* p, Point32 delta) {
    for (int i = 0; i < 4; i++) {
        p->x[i] += delta.x;
        p->y[i] += delta.y;
    }
}

inline void RotateP32_cpp(PackedPoint32* p, float angle) {
    float sin = std::sin(angle);
    float cos = std::cos(angle);
    for (int i = 0; i < 4; i++) {
        auto x = p->x[i];
        auto y = p->y[i];
        p->x[i] = x * cos - y * sin;
        p->y[i] = x * sin + y * cos;
    }
}

inline void TranslateS32_imm(PackedSegment32* s, Point32 delta) {
    auto packed_dx = _mm256_set1_ps(delta.x);
    auto packed_dy = _mm256_set1_ps(delta.y);
    _mm256_store_ps(s->start.x, _mm256_add_ps(_mm256_load_ps(s->start.x), packed_dx));
    _mm256_store_ps(s->start.y, _mm256_add_ps(_mm256_load_ps(s->start.y), packed_dy));
    _mm256_store_ps(s->end.x, _mm256_add_ps(_mm256_load_ps(s->end.x), packed_dx));
    _mm256_store_ps(s->end.y, _mm256_add_ps(_mm256_load_ps(s->end.y), packed_dy));
}

inline void RotateS32_imm(PackedSegment32* s, float angle) {
    float sin = std::sin(angle);
    float cos = std::cos(angle);
    auto pcos = _mm256_set1_ps(cos);
    auto psin = _mm256_set1_ps(sin);

    auto x1 = _mm256_load_ps(s->start.x);
    auto y1 = _mm256_load_ps(s->start.y);
    auto x2 = _mm256_load_ps(s->end.x);
    auto y2 = _mm256_load_ps(s->end.y);
    _mm256_store_ps(s->start.x, _mm256_fmsub_ps(x1, pcos, _mm256_mul_ps(y1, psin))); // xcos - ysin
    _mm256_store_ps(s->start.y, _mm256_fmadd_ps(x1, psin, _mm256_mul_ps(y1, pcos))); // xsin + ycos
    _mm256_store_ps(s->end.x, _mm256_fmsub_ps(x2, pcos, _mm256_mul_ps(y2, psin))); // xcos - ysin
    _mm256_store_ps(s->end.y, _mm256_fmadd_ps(x2, psin, _mm256_mul_ps(y2, pcos))); // xsin + ycos
}

inline void TranslateS32_cpp(PackedSegment32* s, Point32 delta) {
    for (int i = 0; i < 4; i++) {
        s->start.x[i] += delta.x;
        s->start.y[i] += delta.y;
        s->end.x[i] += delta.x;
        s->end.y[i] += delta.y;
    }
}

inline void RotateS32_cpp(PackedSegment32* s, float angle) {
    float sin = std::sin(angle);
    float cos = std::cos(angle);
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
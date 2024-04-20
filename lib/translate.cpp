#include "transform.h"
#include <immintrin.h>

/*
void TranslateF64_imm(PackedPoint* p, Point delta) {
void TranslateI64_intrin(PackedPoint* p, Point delta) {
    auto x_new = _mm256_add_pd(_mm256_load_pd(p->x), _mm256_set1_pd(delta.x));
    auto y_new = _mm256_add_pd(_mm256_load_pd(p->y), _mm256_set1_pd(delta.y));
    _mm256_store_pd(p->x, x_new);
    _mm256_store_pd(p->y, y_new);
}

void TranslateF64_cpp(PackedPoint* p, Point delta) {
void TranslateI64(PackedPoint* p, Point delta) {
    for (int i = 0; i < 4; i++) {
        p->x[i] += delta.x;
        p->y[i] += delta.y;
    }
}
 */
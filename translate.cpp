#include "transform.h"
#include <immintrin.h>

// p_*** = packed
void TranslateI64_intrin(double* x, double* y, double dx, double dy) {
    auto px = _mm256_add_pd(_mm256_load_pd(x), _mm256_set1_pd(dx));
    auto py = _mm256_add_pd(_mm256_load_pd(y), _mm256_set1_pd(dy));
    _mm256_store_pd(x, px);
    _mm256_store_pd(y, py);
}

void TranslateI64(double* x, double* y, double dx, double dy) {
    for (int i = 0; i < 4; i++) {
        x[i] += dx;
        y[i] += dy;
    }
}
#include "transform.h"
#include <immintrin.h>
#include <cmath>

// p_*** = packed
void RotateI64_intrin(double* x, double* y, double angle) {
    double sin = std::sin(angle);
    double cos = std::cos(angle);
    __m256d pcos = _mm256_set1_pd(cos);
    __m256d psin = _mm256_set1_pd(sin);

    __m256d px = _mm256_load_pd(x);
    __m256d py = _mm256_load_pd(y);
    __m256d x_new = _mm256_fmsub_pd(px, pcos, _mm256_mul_pd(py, psin)); // xcos - ysin
    __m256d y_new = _mm256_fmadd_pd(px, psin, _mm256_mul_pd(py, pcos)); // xsin + ycos
    _mm256_store_pd(x, x_new);
    _mm256_store_pd(y, y_new);
}

void RotateI64(double* x, double* y, double angle) {
    double sin = std::sin(angle);
    double cos = std::cos(angle);
    for (int i = 0; i < 4; i++) {
        x[i] = x[i] * cos - y[i] * sin;
        y[i] = x[i] * sin + y[i] * cos;
    }
}
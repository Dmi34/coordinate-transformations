#include "transform.h"
#include <immintrin.h>
#include <cmath>

/*
void RotateI64_intrin(PackedPoint* p, double angle) {
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

void RotateI64(PackedPoint* p, double angle) {
    double sin = std::sin(angle);
    double cos = std::cos(angle);
    for (int i = 0; i < 4; i++) {
        p->x[i] = p->x[i] * cos - p->y[i] * sin;
        p->y[i] = p->x[i] * sin + p->y[i] * cos;
    }
}
*/
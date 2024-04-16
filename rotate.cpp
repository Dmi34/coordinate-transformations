#include "transform.h"
#include <immintrin.h>
#include <iostream>
#include <cmath>

// Shift segment with immintrin
// void shift_segment(__m256d* segment1, __m256d* segment2, double dx, double dy) {
//     __m256d delta = _mm256_set_pd(dx, dx, dx, dx);
//     __m256d shifted_segment1 = _mm256_add_pd(*segment1, delta);
//     delta = _mm256_set_pd(dy, dy, dy, dy);
//     __m256d shifted_segment2 = _mm256_add_pd(*segment2, delta);
//     *segment1 = shifted_segment1;
//     *segment2 = shifted_segment2;
//     return;
// }

void RotateI64_avx2(double *x_values, double *y_values, double theta, int num_points) {
    double cos_theta = std::cos(theta);
    double sin_theta = std::sin(theta);
    __m256d cos_vals = _mm256_set1_pd(cos_theta);
    __m256d sin_vals = _mm256_set1_pd(sin_theta);
    for (int i = 0; i < num_points; i += 4) {
        __m256d x = _mm256_load_pd(&x_values[i]);
        __m256d y = _mm256_load_pd(&y_values[i]);
        __m256d x_prime = _mm256_fmsub_pd(x, cos_vals, _mm256_mul_pd(y, sin_vals));
        __m256d y_prime = _mm256_fmadd_pd(x, sin_vals, _mm256_mul_pd(y, cos_vals));
        _mm256_store_pd(&x_values[i], x_prime);
        _mm256_store_pd(&y_values[i], y_prime);
    }
}

#pragma once

#include "immintrin.h"

extern "C" void TranslateI64_avx2(__m256d* x, __m256d* y, double dx, double dy);

inline void RotateI64_avx2(double *x_values, double *y_values, double theta, int num_points);


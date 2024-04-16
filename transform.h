#pragma once

#include "immintrin.h"

extern "C" void TranslateI64_avx2(double* x, double* y, double dx, double dy);
extern "C" void RotateI64_avx2(double* x, double* y, double sin, double cos);

inline void RotateI64_avx2(double* x, double* y, double angle);

//inline void TranslateI64_avx2(double *x, double *y, double dx, double dy);

//inline void RotateI64_avx2(double *x_values, double *y_values, double theta, int num_points);


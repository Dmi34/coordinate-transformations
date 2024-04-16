#pragma once

#include "immintrin.h"

extern "C" void TranslateI64_avx2(double* x, double* y, double dx, double dy);
extern "C" void RotateI64_avx2(double* x, double* y, double sin, double cos);
inline void RotateI64_avx2(double* x, double* y, double angle);

void TranslateI64_intrin(double *x, double *y, double dx, double dy);
void RotateI64_intrin(double *x_values, double *y_values, double theta);

void TranslateI64(double *x, double *y, double dx, double dy);
void RotateI64(double *x_values, double *y_values, double theta);
#pragma once

#include "immintrin.h"

extern "C" void TranslateI64_avx2(__m256d* x, __m256d* y, double dx, double dy);
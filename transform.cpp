#include "transform.h"
#include <cmath>

inline void RotateI64_avx2(double* x, double* y, double angle) {
    RotateI64_avx2(x, y, std::sin(angle), std::cos(angle));
}
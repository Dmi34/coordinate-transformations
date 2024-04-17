#pragma once

#include "immintrin.h"
#include <cmath>

struct alignas(16) Point {
    double x;
    double y;
};

struct alignas(16) PackedPoint {
    double* x;
    double* y;
};

struct alignas(16) Segment {
    Point start;
    Point end;
};

struct alignas(16) PackedSegment {
    PackedPoint start;
    PackedPoint end;
};

extern "C" void TranslateI64_avx2(PackedPoint* p, Point delta);
extern "C" void RotateI64_avx2(PackedPoint* p, double sin, double cos);
inline void RotateI64_avx2(PackedPoint* p, double angle) {
    RotateI64_avx2(p, std::sin(angle), std::cos(angle));
}

void TranslateI64_intrin(PackedPoint* p, Point delta);
void RotateI64_intrin(PackedPoint* p, double angle);

void TranslateI64(PackedPoint* p, Point delta);
void RotateI64(PackedPoint* p, double angle);


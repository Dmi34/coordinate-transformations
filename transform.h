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

extern "C" void TranslateF64_asm(PackedPoint* p, Point delta);
extern "C" void RotateF64_asm(PackedPoint* p, double sin, double cos);
inline void RotateF64_asm(PackedPoint* p, double angle) {
    RotateF64_asm(p, std::sin(angle), std::cos(angle));
}

void TranslateF64_imm(PackedPoint* p, Point delta);
void RotateF64_imm(PackedPoint* p, double angle);

void TranslateF64_cpp(PackedPoint* p, Point delta);
void RotateF64_cpp(PackedPoint* p, double angle);


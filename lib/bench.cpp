#include "transform.h"
#include <cmath>
#include <iostream>
#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark_all.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_range_equals.hpp>

Point delta{1, 1};
TEST_CASE("BENCHMARKS FOR TRANSLATE") { 
    double x[4] = {1, 2, 3, 4};
    double y[4] = {1, 2, 3, 4};
    PackedPoint p{x, y};
    BENCHMARK("TEST TranslateF64_asm") {
        return TranslateF64_asm(&p, delta);
    };
    double x1[4] = {1, 2, 3, 4};
    double y1[4] = {1, 2, 3, 4};
    PackedPoint p1{x1, y1};
    BENCHMARK("TEST TranslateF64_imm") {
        return TranslateF64_imm(&p1, delta);
    };
    double x2[4] = {1, 2, 3, 4};
    double y2[4] = {1, 2, 3, 4};
    PackedPoint p2{x2, y2};
    BENCHMARK("TEST TranslateF64_cpp") {
        return TranslateF64_cpp(&p2, delta);
    };
}

double x_new[4] = {1, 2, 3, 4};
double y_new[4] = {1, 2, 3, 4};
PackedPoint p1{x_new, y_new};
double angle = M_PI / 4;
TEST_CASE("BENCHMARKS FOR ROTATE") {
    BENCHMARK("TEST RotateF64_asm") {
        return RotateF64_imm(&p1, angle);
    };
    BENCHMARK("TEST RotateF64_imm") {
        return RotateF64_imm(&p1, angle);
    };
    BENCHMARK("TEST RotateF64_cpp") {
        return RotateF64_cpp(&p1, angle);
    };
}

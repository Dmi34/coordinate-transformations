#include "transform64.h"
#include <cmath>
#include <iostream>
#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark_all.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_range_equals.hpp>

Point64 delta{1, 1};
TEST_CASE("BENCHMARKS FOR TRANSLATE") {
    alignas(32) double x[4] = {1, 2, 3, 4};
    alignas(32) double y[4] = {1, 2, 3, 4};
    PackedPoint64 p{x, y};
    BENCHMARK("TEST TranslateP64_asm") {
        return TranslateP64_asm(&p, delta);
    };
    alignas(32) double x1[4] = {1, 2, 3, 4};
    alignas(32) double y1[4] = {1, 2, 3, 4};
    PackedPoint64 p1{x1, y1};
    BENCHMARK("TEST TranslateP64_imm") {
        return TranslateP64_imm(&p1, delta);
    };
    alignas(32) double x2[4] = {1, 2, 3, 4};
    alignas(32) double y2[4] = {1, 2, 3, 4};
    PackedPoint64 p2{x2, y2};
    BENCHMARK("TEST TranslateP64_cpp") {
        return TranslateP64_cpp(&p2, delta);
    };
}

alignas(32) double x_new[4] = {1, 2, 3, 4};
alignas(32) double y_new[4] = {1, 2, 3, 4};
PackedPoint64 p1{x_new, y_new};
double angle = M_PI / 4;
TEST_CASE("BENCHMARKS FOR ROTATE") {
    BENCHMARK("TEST RotateP64_asm") {
        return RotateP64_imm(&p1, angle);
    };
    BENCHMARK("TEST RotateP64_imm") {
        return RotateP64_imm(&p1, angle);
    };
    BENCHMARK("TEST RotateP64_cpp") {
        return RotateP64_cpp(&p1, angle);
    };
}

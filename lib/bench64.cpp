#include "transform64.h"
#include <cmath>
#include <iostream>
#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark_all.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_range_equals.hpp>

using namespace DoubleGeometry;

TEST_CASE("BENCHMARKS FOR TRANSLATE") {
    Point delta{1, 1};
    double x[4] = {1, 2, 3, 4};
    double y[4] = {1, 2, 3, 4};
    PackedPoint p{x, y};
    // BENCHMARK("TEST TranslateP64_asm") {
    //     return TranslateP64_asm(p, delta);
    // };
    BENCHMARK("TEST TranslateP64_imm") {
        return Translate_imm(p, delta);
    };
    BENCHMARK("TEST TranslateP64_cpp") {
        return Translate_cpp(p, delta);
    };
}

TEST_CASE("BENCHMARKS FOR ROTATE") {
    double x[4] = {1, 2, 3, 4};
    double y[4] = {1, 2, 3, 4};
    PackedPoint p{x, y};
    double angle = M_PI / 4;
    // BENCHMARK("TEST RotateP64_asm") {
    //     return RotateP64_asm(p, angle);
    // };
    BENCHMARK("TEST RotateP64_imm") {
        return Rotate_imm(p, angle);
    };
    BENCHMARK("TEST RotateP64_cpp") {
        return Rotate_cpp(p, angle);
    };
}

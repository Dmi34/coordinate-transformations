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
    PackedPoint dummy;
    BENCHMARK("TEST TranslateP64_asm unwrapped") {
        return Translate_asm(&dummy, p, delta);
    };
    BENCHMARK("TEST TranslateP64_asm wrapped") {
        return Translate_asm(p, delta);
    };
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
    PackedPoint dummy;
    DoubleDirection dir(angle);
    BENCHMARK("TEST RotateP64_asm unwrapped") {
        return Rotate_asm(&dummy, p, dir);
    };
    BENCHMARK("TEST RotateP64_asm wrapped") {
        return Rotate_asm(p, angle);
    };
    BENCHMARK("TEST RotateP64_imm") {
        return Rotate_imm(p, angle);
    };
    BENCHMARK("TEST RotateP64_cpp") {
        return Rotate_cpp(p, angle);
    };
}

TEST_CASE("BENCHMARKS FOR TRANSLATE SEGMENT") {
    Point delta{1, 1};
    double x1[4] = {1, 2, 3, 4};
    double x2[4] = {2, 3, 4, 5};
    double y1[4] = {1, 2, 3, 4};
    double y2[4] = {2, 3, 4, 5};
    PackedSegment seg{{x1, y1}, {x2, y2}};
    BENCHMARK("TEST Translate_imm") {
        return Translate_imm(seg, delta);
    };
    BENCHMARK("TEST Translate_cpp") {
        return Translate_cpp(seg, delta);
    };
}

TEST_CASE("BENCHMARKS FOR ROTATE SEGMENT") {
    double angle = M_PI_2;
    double x1[4] = {1, 2, 3, 4};
    double x2[4] = {2, 3, 4, 5};
    double y1[4] = {1, 2, 3, 4};
    double y2[4] = {2, 3, 4, 5};
    PackedSegment seg{{x1, y1}, {x2, y2}};
    BENCHMARK("TEST Rotate_imm") {
        return Rotate_imm(seg, angle);
    };
    BENCHMARK("TEST Rotate_cpp") {
        return Rotate_cpp(seg, angle);
    };
}


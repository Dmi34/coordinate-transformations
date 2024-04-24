#include "transform32.h"
#include <cmath>
#include <iostream>
#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark_all.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_range_equals.hpp>

using namespace SingleGeometry;

TEST_CASE("BENCHMARKS FOR TRANSLATE") {
    Point delta{1, 1};
    float x[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    float y[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    PackedPoint p{x, y};
    // BENCHMARK("TEST TranslateP64_asm") {
    //     return TranslateP64_asm(p, delta);
    // };
    BENCHMARK("TEST TranslateP32_imm") {
        return Translate_imm(p, delta);
    };
    BENCHMARK("TEST TranslateP32_cpp") {
        return Translate_cpp(p, delta);
    };
}

TEST_CASE("BENCHMARKS FOR ROTATE") {
    float x[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    float y[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    PackedPoint p{x, y};
    float angle = M_PI / 4;
    // BENCHMARK("TEST RotateP64_asm") {
    //     return RotateP64_asm(p, angle);
    // };
    BENCHMARK("TEST RotateP32_imm") {
        return Rotate_imm(p, angle);
    };
    BENCHMARK("TEST RotateP32_cpp") {
        return Rotate_cpp(p, angle);
    };
}

TEST_CASE("BENCHMARKS FOR TRANSLATE SEGMENT") {
    Point delta{1, 1};
    float x1[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    float x2[8] = {2, 3, 4, 5, 6, 7, 8, 9};
    float y1[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    float y2[8] = {2, 3, 4, 5, 6, 7, 8, 9};
    PackedSegment seg{{x1, y1}, {x2, y2}};
    BENCHMARK("TEST Translate_imm") {
        return Translate_imm(seg, delta);
    };
    BENCHMARK("TEST Translate_cpp") {
        return Translate_cpp(seg, delta);
    };
}

TEST_CASE("BENCHMARKS FOR ROTATE SEGMENT") {
    float angle = M_PI_2;
    float x1[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    float x2[8] = {2, 3, 4, 5, 6, 7, 8, 9};
    float y1[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    float y2[8] = {2, 3, 4, 5, 6, 7, 8, 9};
    PackedSegment seg{{x1, y1}, {x2, y2}};
    BENCHMARK("TEST Rotate_imm") {
        return Rotate_imm(seg, angle);
    };
    BENCHMARK("TEST Rotate_cpp") {
        return Rotate_cpp(seg, angle);
    };
}


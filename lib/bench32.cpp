#include "transform.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark_all.hpp>
#include <cmath>
#include <iostream>

using namespace SingleGeometry;

TEST_CASE("BENCHMARKS FOR SINGLE PRECISION POINTS") {
    float x[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    float y[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    PackedPoint p{x, y};
    
    Point delta{1, 1};
    BENCHMARK("TEST TranslateImm") {
        return TranslateImm(p, delta);
    };

    float angle = M_PI / 4;
    BENCHMARK("TEST RotateImm") {
        return RotateImm(p, angle);
    };
}

TEST_CASE("BENCHMARKS FOR SINGLE PRECISION SEGMENTS") {
    float x1[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    float x2[8] = {2, 3, 4, 5, 6, 7, 8, 9};
    float y1[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    float y2[8] = {2, 3, 4, 5, 6, 7, 8, 9};
    PackedSegment seg{{x1, y1}, {x2, y2}};

    Point delta{1, 1};
    BENCHMARK("TEST TranslateImm") {
        return TranslateImm(seg, delta);
    };

    float angle = M_PI_2;
    BENCHMARK("TEST RotateImm") {
        return RotateImm(seg, angle);
    };
}


#include "transform.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark_all.hpp>
#include <cmath>
#include <iostream>

using namespace DoubleGeometry;

TEST_CASE("BENCHMARKS FOR DOUBLE PRECISION POINTS") {
    double x[4] = {1, 2, 3, 4};
    double y[4] = {1, 2, 3, 4};
    PackedPoint p{x, y};

    Point delta{1, 1};
    BENCHMARK("TEST TranslateImm") {
        return TranslateImm(p, delta);
    };

    double angle = M_PI / 4;
    BENCHMARK("TEST RotateImm") {
        return RotateImm(p, angle);
    };
}

TEST_CASE("BENCHMARKS FOR DOUBLE PRECISION SEGMENTS") {
    double x1[4] = {1, 2, 3, 4};
    double x2[4] = {2, 3, 4, 5};
    double y1[4] = {1, 2, 3, 4};
    double y2[4] = {2, 3, 4, 5};
    PackedSegment seg{{x1, y1}, {x2, y2}};

    Point delta{1, 1};
    BENCHMARK("TEST TranslateImm") {
        return TranslateImm(seg, delta);
    };

    double angle = M_PI_2;
    BENCHMARK("TEST RotateImm") {
        return RotateImm(seg, angle);
    };
}


#include "transform.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark_all.hpp>
#include <cmath>
#include <iostream>
#include <numbers>

TEST_CASE("BENCHMARKS FOR POINTS") {
{
    using namespace DoubleGeometry;
    double x[4] = {1, 2, 3, 4};
    double y[4] = {1, 2, 3, 4};
    PackedPoint p{x, y};

    Point delta{1, 1};
    BENCHMARK("Double-precision TranslateImm") {
    return TranslateImm(p, delta);
    };

    double angle = std::numbers::pi / 4;
    BENCHMARK("Double-precision RotateImm") {
    return RotateImm(p, angle);
    };
}

{
    using namespace SingleGeometry;
    float x[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    float y[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    PackedPoint p{x, y};

    Point delta{1, 1};
    BENCHMARK("Single-precision TranslateImm") {
        return TranslateImm(p, delta);
    };

    float angle = std::numbers::pi / 4;
    BENCHMARK("Single-precision RotateImm") {
        return RotateImm(p, angle);
    };
}
}

TEST_CASE("BENCHMARKS FOR SEGMENTS") {
{
    using namespace DoubleGeometry;
    double x1[4] = {1, 2, 3, 4};
    double x2[4] = {2, 3, 4, 5};
    double y1[4] = {1, 2, 3, 4};
    double y2[4] = {2, 3, 4, 5};
    PackedSegment seg{{x1, y1}, {x2, y2}};

    Point delta{1, 1};
    BENCHMARK("Double-precision TranslateImm") {
        return TranslateImm(seg, delta);
    };

    double angle = std::numbers::pi / 2;
    BENCHMARK("Double-precision RotateImm") {
        return RotateImm(seg, angle);
    };
}

{
    using namespace SingleGeometry;
    float x1[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    float x2[8] = {2, 3, 4, 5, 6, 7, 8, 9};
    float y1[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    float y2[8] = {2, 3, 4, 5, 6, 7, 8, 9};
    PackedSegment seg{{x1, y1}, {x2, y2}};

    Point delta{1, 1};
    BENCHMARK("Single-precision TranslateImm") {
        return TranslateImm(seg, delta);
    };

    float angle = std::numbers::pi / 2;
    BENCHMARK("Single-precision RotateImm") {
        return RotateImm(seg, angle);
    };
}
}
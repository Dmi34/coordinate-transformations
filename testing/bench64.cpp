#include "transform.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark_all.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_range_equals.hpp>
#include <cmath>
#include <iostream>

using namespace DoubleGeometry;

TEST_CASE("BENCHMARKS FOR TRANSLATE") {
    Point delta{1, 1};
    double x[4] = {1, 2, 3, 4};
    double y[4] = {1, 2, 3, 4};
    PackedPoint p{x, y};
//    PackedPoint dummy;
//    BENCHMARK("TEST TranslateAsm (unwrapped)") {
//        return TranslateAsm(&dummy, p, delta);
//    };
//    BENCHMARK("TEST TranslateAsm wrapped") {
//        return TranslateAsm(p, delta);
//    };
    BENCHMARK("TEST TranslateImm") {
        return TranslateImm(p, delta);
    };
    BENCHMARK("TEST TranslateCpp") {
        return TranslateCpp(p, delta);
    };
}

TEST_CASE("BENCHMARKS FOR ROTATE") {
    double x[4] = {1, 2, 3, 4};
    double y[4] = {1, 2, 3, 4};
    PackedPoint p{x, y};
    double angle = M_PI / 4;
//    PackedPoint dummy;
//    Direction dir(angle);
//    BENCHMARK("TEST RotateAsm (unwrapped)") {
//        return RotateAsm(&dummy, p, dir);
//    };
//    BENCHMARK("TEST RotateAsm wrapped") {
//        return RotateAsm(p, angle);
//    };
    BENCHMARK("TEST RotateImm") {
        return RotateImm(p, angle);
    };
    BENCHMARK("TEST RotateCpp") {
        return RotateCpp(p, angle);
    };
}

TEST_CASE("BENCHMARKS FOR TRANSLATE SEGMENT") {
    Point delta{1, 1};
    double x1[4] = {1, 2, 3, 4};
    double x2[4] = {2, 3, 4, 5};
    double y1[4] = {1, 2, 3, 4};
    double y2[4] = {2, 3, 4, 5};
    PackedSegment seg{{x1, y1}, {x2, y2}};
//    PackedSegment dummy;
//    BENCHMARK("TEST TranslateSegmentAsm (unwrapped)") {
//        return TranslateSegmentAsm(&dummy, seg, delta);
//    };
//    BENCHMARK("TEST TranslateAsm wrapped") {
//        return TranslateAsm(seg, delta);
//    };
    BENCHMARK("TEST TranslateImm") {
        return TranslateImm(seg, delta);
    };
    BENCHMARK("TEST TranslateCpp") {
        return TranslateCpp(seg, delta);
    };
}

TEST_CASE("BENCHMARKS FOR ROTATE SEGMENT") {
    double angle = M_PI_2;
    double x1[4] = {1, 2, 3, 4};
    double x2[4] = {2, 3, 4, 5};
    double y1[4] = {1, 2, 3, 4};
    double y2[4] = {2, 3, 4, 5};
    Direction dir(angle);
    PackedSegment seg{{x1, y1}, {x2, y2}};
//    PackedSegment dummy;
//    BENCHMARK("TEST RotateSegmentAsm (unwrapped)") {
//        return RotateSegmentAsm(&dummy, seg, dir);
//    };
//    BENCHMARK("TEST RotateAsm wrapped") {
//        return RotateAsm(seg, angle);
//    };
    BENCHMARK("TEST RotateImm") {
        return RotateImm(seg, angle);
    };
    BENCHMARK("TEST RotateCpp") {
        return RotateCpp(seg, angle);
    };
}


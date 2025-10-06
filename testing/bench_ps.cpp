#include "transform.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark_all.hpp>
#include <numbers>

using namespace SingleGeometry;

TEST_CASE("BENCHMARKS FOR TRANSLATE POINT") {
    Point delta{1, 1};
    float x[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    float y[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    PackedPoint p{x, y};
    PackedPoint dummy;
    BENCHMARK("TEST TranslateSinglePointAsm") {
        return TranslateSinglePointAsm(&dummy, p, delta);
    };
    BENCHMARK("TEST TranslateAsm") {
        return TranslateAsm(p, delta);
    };
    BENCHMARK("TEST TranslateImm") {
        return TranslateImm(p, delta);
    };
    BENCHMARK("TEST TranslateCpp") {
        return TranslateCpp(p, delta);
    };
}

TEST_CASE("BENCHMARKS FOR ROTATE POINT") {
    float x[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    float y[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    PackedPoint p{x, y};
    float angle = std::numbers::pi / 4;
    PackedPoint dummy;
    Direction dir(angle);
    BENCHMARK("TEST RotateSinglePointAsm") {
        return RotateSinglePointAsm(&dummy, p, dir);
    };
    BENCHMARK("TEST RotateAsm") {
        return RotateAsm(p, angle);
    };
    BENCHMARK("TEST RotateImm") {
        return RotateImm(p, angle);
    };
    BENCHMARK("TEST RotateCpp") {
        return RotateCpp(p, angle);
    };
}

TEST_CASE("BENCHMARKS FOR TRANSLATE SEGMENT") {
    Point delta{1, 1};
    float x1[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    float x2[8] = {2, 3, 4, 5, 6, 7, 8, 9};
    float y1[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    float y2[8] = {2, 3, 4, 5, 6, 7, 8, 9};
    PackedSegment seg{{x1, y1}, {x2, y2}};
    PackedSegment dummy;
    BENCHMARK("TEST TranslateSingleSegmentAsm") {
        return TranslateSingleSegmentAsm(&dummy, seg, delta);
    };
    BENCHMARK("TEST TranslateAsm") {
        return TranslateAsm(seg, delta);
    };
    BENCHMARK("TEST TranslateImm") {
        return TranslateImm(seg, delta);
    };
    BENCHMARK("TEST TranslateCpp") {
        return TranslateCpp(seg, delta);
    };
}

TEST_CASE("BENCHMARKS FOR ROTATE SEGMENT") {
    float angle = std::numbers::pi / 2;
    float x1[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    float x2[8] = {2, 3, 4, 5, 6, 7, 8, 9};
    float y1[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    float y2[8] = {2, 3, 4, 5, 6, 7, 8, 9};
    PackedSegment seg{{x1, y1}, {x2, y2}};
    PackedSegment dummy;
    Direction dir(angle);
    BENCHMARK("TEST RotateSingleSegmentAsm") {
        return RotateSingleSegmentAsm(&dummy, seg, dir);
    };
    BENCHMARK("TEST RotateAsm") {
        return RotateAsm(seg, angle);
    };
    BENCHMARK("TEST RotateImm") {
        return RotateImm(seg, angle);
    };
    BENCHMARK("TEST RotateCpp") {
        return RotateCpp(seg, angle);
    };
}


#include "transform.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark_all.hpp>

using namespace DoubleGeometry;

TEST_CASE("BENCHMARKS FOR TRANSLATE POINT") {
    Point delta{1, 1};
    double x[4] = {1, 2, 3, 4};
    double y[4] = {1, 2, 3, 4};
    PackedPoint p{x, y};
   PackedPoint dummy;
   BENCHMARK("TEST TranslateDoublePointAsm") {
       return TranslateDoublePointAsm(&dummy, p, delta);
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
    double x[4] = {1, 2, 3, 4};
    double y[4] = {1, 2, 3, 4};
    PackedPoint p{x, y};
    double angle = M_PI / 4;
   PackedPoint dummy;
   Direction dir(angle);
   BENCHMARK("TEST RotateDoublePointAsm") {
       return RotateDoublePointAsm(&dummy, p, dir);
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
    double x1[4] = {1, 2, 3, 4};
    double x2[4] = {2, 3, 4, 5};
    double y1[4] = {1, 2, 3, 4};
    double y2[4] = {2, 3, 4, 5};
    PackedSegment seg{{x1, y1}, {x2, y2}};
   PackedSegment dummy;
   BENCHMARK("TEST TranslateDoubleSegmentAsm") {
       return TranslateDoubleSegmentAsm(&dummy, seg, delta);
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
    double angle = M_PI_2;
    double x1[4] = {1, 2, 3, 4};
    double x2[4] = {2, 3, 4, 5};
    double y1[4] = {1, 2, 3, 4};
    double y2[4] = {2, 3, 4, 5};
    Direction dir(angle);
    PackedSegment seg{{x1, y1}, {x2, y2}};
   PackedSegment dummy;
   BENCHMARK("TEST RotateDoubleSegmentAsm") {
       return RotateDoubleSegmentAsm(&dummy, seg, dir);
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


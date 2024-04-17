#include "transform.h"
#include <cmath>
#include <iostream>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_range_equals.hpp>

TEST_CASE("BEBRA") {
    REQUIRE(5 == 5);
    Point delta{1, 1};
    double x[4] = {1, 2, 3, 4};
    double y[4] = {1, 2, 3, 4};
    PackedPoint p{x, y};
    TranslateI64_intrin(&p, delta);
    REQUIRE(x[0] == 2);
    REQUIRE(y[0] == 2);
}

TEST_CASE("BENCHMARKS") {
    Point delta{1, 1};
    double x[4] = {1, 2, 3, 4};
    double y[4] = {1, 2, 3, 4};
    PackedPoint p{x, y};
    return TranslateI64_intrin(&p, delta);
}
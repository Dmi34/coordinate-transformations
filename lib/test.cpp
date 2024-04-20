#include "transform.h"
#include <cmath>
#include <iostream>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_range_equals.hpp>

Point delta{1, 1};
double x[4] = {1, 2, 3, 4};
double y[4] = {1, 2, 3, 4};
PackedPoint p{x, y};

TEST_CASE("TEST") {
    TranslateF64_imm(&p, delta);
    REQUIRE("5 == 5");
}
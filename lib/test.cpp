#include "transform.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <catch2/catch_test_macros.hpp>
//#include <catch2/matchers/catch_matchers.hpp>
//#include <catch2/matchers/catch_matchers_range_equals.hpp>

void CheckEq(const PackedPoint& lhs, const PackedPoint& rhs) {
    for (int i = 0; i < 4; i++) {
        REQUIRE(lhs.x[i] == rhs.x[i]);
        REQUIRE(lhs.y[i] == rhs.y[i]);
    }
}

void Print(const PackedPoint& p, std::string message = "") {
    std::cout << message;
    for (int i = 0; i < 4; i++) {
        std::cout << std::fixed << std::setprecision(5) << "{" << p.x[i] << ";" << p.y[i] << "} ";
    }
    std::cout << '\n';
}

TEST_CASE("Test TranslateF64_imm") {
    Point delta{1.5, 2.75};
    double x[4] = {1, 2.3, 3, 4.2};
    double y[4] = {5, 6.142353556, 7, 8.15};
    PackedPoint p1{x, y};
    PackedPoint p2{x, y};
    TranslateF64_imm(&p1, delta);
    TranslateF64_cpp(&p2, delta);
    CheckEq(p1, p2);
}

TEST_CASE("Test RotateF64_imm") {
//    double angle = M_PI_4;
//    double x[4] = {1, 0, -1, 0};
//    double y[4] = {0, 1, 0, -1};
//    PackedPoint p1{x, y};
//    PackedPoint p2{x, y};
//    RotateF64_imm(&p1, angle);
//    RotateF64_cpp(&p2, angle);
//    CheckEq(p1, p2);
//    Print(p1, "imm: ");
//    Print(p2, "cpp: ");
}


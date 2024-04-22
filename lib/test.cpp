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
    std::cout << message << '\n';
    for (int i = 0; i < 4; i++) {
        std::cout << std::fixed << std::setprecision(5) << "{" << p.x[i] << ";" << p.y[i] << "} ";
    }
    std::cout << '\n';
}

TEST_CASE("Test TranslateF64") {
    Point delta{1.0, 2.0};
    double x[4] = {1.0, 2.0, 3.0, 4.0};
    double y[4] = {0.0, 6.0, 7.0, 8.0};
    double x1[4] = {1.0, 2.0, 3.0, 4.0};
    double y1[4] = {0.0, 6.0, 7.0, 8.0};
    double x2[4] = {1.0, 2.0, 3.0, 4.0};
    double y2[4] = {0.0, 6.0, 7.0, 8.0};
    PackedPoint p1{x1, y1};
    PackedPoint p2{x2, y2};
    PackedPoint p3{x, y};
    Print(p1, "Given to translate by delta:");
    TranslateF64_asm(&p1, delta);
    TranslateF64_imm(&p2, delta);
    TranslateF64_cpp(&p3, delta);
    CheckEq(p1, p2);
    CheckEq(p2, p3);
    Print(p1, "asm: ");
    Print(p2, "imm: ");
    Print(p3, "cpp: ");
}

TEST_CASE("Test RotateF64") {
    double angle = M_PI_2;
    double x1[4] = {1, 0, -1, 0};
    double y1[4] = {0, 1, 0, -1};
    double x2[4] = {1, 0, -1, 0};
    double y2[4] = {0, 1, 0, -1};
    double x3[4] = {1, 0, -1, 0};
    double y3[4] = {0, 1, 0, -1};
    PackedPoint p1{x1, y1};
    PackedPoint p2{x2, y2};
    PackedPoint p3{x3, y3};
    Print(p1, "given to rotate by angle: ");
    RotateF64_asm(&p1, std::sin(angle), std::cos(angle));
    RotateF64_imm(&p2, angle);
    RotateF64_cpp(&p3, angle);
    CheckEq(p1, p2);
    CheckEq(p2, p3);
    Print(p1, "asm: ");
    Print(p2, "imm: ");
    Print(p3, "cpp: ");
}

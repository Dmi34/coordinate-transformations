#include "transform64.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <random>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_range_equals.hpp>

using namespace DoubleGeometry;

void CheckEq(const PackedPoint& lhs, const PackedPoint& rhs) {
    for (int i = 0; i < 4; i++) {
        REQUIRE(lhs.x[i] == rhs.x[i]);
        REQUIRE(lhs.y[i] == rhs.y[i]);
    }
}

void CheckEq(const PackedSegment& lhs, const PackedSegment& rhs) {
    for (int i = 0; i < 4; i++) {
        CheckEq(lhs.start, rhs.start);
        CheckEq(lhs.finish, rhs.finish);
    }
}

void Print(const PackedPoint& p, std::string message = "") {
    std::cout << message << '\n';
    for (int i = 0; i < 4; i++) {
        std::cout << std::fixed << std::setprecision(5) << "{" << p.x[i] << ";" << p.y[i] << "} ";
    }
    std::cout << '\n';
}

TEST_CASE("Test Translate Point") {
    std::default_random_engine gen;
    std::uniform_real_distribution<double> distr(-100000.0, 100000.0);
    for(size_t k = 0; k < 100000; ++k) {
        Point delta{distr(gen), distr(gen)};
        double points[4][4];
        for(size_t i = 0; i < 2; ++i) {
            for(size_t j = 0; j < 4; ++j) {
                points[i][j] = distr(gen);
                points[i+2][j] = points[i][j];
            }
        }
        PackedPoint p1{points[0], points[1]};
        PackedPoint p2{points[2], points[3]};
        CheckEq(Translate_imm(p1, delta), Translate_cpp(p2, delta));
    }
}

TEST_CASE("Test Rotate Point") {
    std::default_random_engine gen;
    std::uniform_real_distribution<double> distr(-100000.0, 100000.0);
    for(size_t k = 0; k < 100000; ++k) {
        double angle = distr(gen);
        double points[4][4];
        for(size_t i = 0; i < 2; ++i) {
            for(size_t j = 0; j < 4; ++j) {
                points[i][j] = distr(gen);
                points[i+2][j] = points[i][j];
            }
        }
        PackedPoint p1{points[0], points[1]};
        PackedPoint p2{points[2], points[3]};
        CheckEq(Rotate_imm(p1, angle), Rotate_cpp(p2, angle));
    }
}

TEST_CASE("Test Translate Segment") {
    std::default_random_engine gen;
    std::uniform_real_distribution<double> distr(-100000.0, 100000.0);
    for(size_t k = 0; k < 100000; ++k) {
        Point delta{distr(gen), distr(gen)};
        double points1[4][4];
        double points2[4][4];
        for(size_t i = 0; i < 2; ++i) {
            for(size_t j = 0; j < 4; ++j) {
                points1[i][j] = distr(gen);
                points2[i][j] = distr(gen);
                points1[i+2][j] = points1[i][j];
                points2[i+2][j] = points2[i][j];
            }
        }
        PackedPoint p1{points1[0], points1[1]};
        PackedPoint p2{points1[2], points1[3]};
        PackedPoint p3{points2[0], points2[1]};
        PackedPoint p4{points2[2], points2[3]};
        PackedSegment seg1{p1, p2};
        PackedSegment seg2{p1, p2};
        CheckEq(Translate_cpp(seg1, delta), Translate_imm(seg2, delta));
    }
}

TEST_CASE("Test Rotate Segmanet") {
    std::default_random_engine gen;
    std::uniform_real_distribution<double> distr(-100000.0, 100000.0);
    for(size_t k = 0; k < 100000; ++k) {
        double angle = distr(gen);
        double points1[4][4];
        double points2[4][4];
        for(size_t i = 0; i < 2; ++i) {
            for(size_t j = 0; j < 4; ++j) {
                points1[i][j] = distr(gen);
                points2[i][j] = distr(gen);
                points1[i+2][j] = points1[i][j];
                points2[i+2][j] = points2[i][j];
            }
        }
        PackedPoint p1{points1[0], points1[1]};
        PackedPoint p2{points1[2], points1[3]};
        PackedPoint p3{points2[0], points2[1]};
        PackedPoint p4{points2[2], points2[3]};
        PackedSegment seg1{p1, p2};
        PackedSegment seg2{p1, p2};
        CheckEq(Rotate_cpp(seg1, angle), Rotate_imm(seg2, angle));
    }
}



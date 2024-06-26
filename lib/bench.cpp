#include "transform.h"
#include <cmath>
#include <iostream>
#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark_all.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_range_equals.hpp>

Point delta{1, 1};
double x[4] = {1, 2, 3, 4};
double y[4] = {1, 2, 3, 4};
PackedPoint p{x, y};

TEST_CASE("BENCHMARKS FOR TRANSLATE") { 
    BENCHMARK("TEST TranslateF64_imm") {
        return TranslateF64_imm(&p, delta);
    };
    BENCHMARK("TEST TranslateF64_cpp") {
        return TranslateF64_cpp(&p, delta);
    };
}

// Problem with 'always_inline' in avx2

// double x_new[4] = {1, 2, 3, 4};
// double y_new[4] = {1, 2, 3, 4};
// PackedPoint p1{x_new, y_new};
// double angle = M_PI / 4;
// TEST_CASE("BENCHMARKS FOR ROTATE") { 
//     BENCHMARK("TEST TranslateI64_intrin") {
//         return RotateI64_intrin(&p1, angle);
//     };
//     BENCHMARK("TEST TranslateI64") {
//         return RotateI64(&p1, angle);
//     };
// }

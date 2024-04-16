#include "transform.h"
#include <cmath>
#include <iostream>

void TestTranslate() {
    double x[4] = {1.0, 2.0, 3.0, 4.0};
    double y[4] = {5.0, 6.0, 7.0, 8.0};
    __m256d a = _mm256_load_pd(x);
    __m256d b = _mm256_load_pd(y);
    TranslateI64_avx2(&a, &b, -2, 8);
    _mm256_store_pd(x, a);
    _mm256_store_pd(y, b);
    for (int i = 0; i < 4; i++) {
        std::cout << x[i] << " ";
    }
    std::cout << '\n';
    for (int i = 0; i < 4; i++) {
        std::cout << y[i] << " ";
    }
}

void TestRotate() {
    double x_points[4] = {1.0, 2.0, 3.0, 4.0};
    double y_points[4] = {1.0, 2.0, 3.0, 4.0};
    double angle = M_PI / 2;
    RotateI64_avx2(x_points, y_points, angle, 4);
    for (int i = 0; i < 4; i++) {
        std::cout << x_points[i] << " ";
    }
    std::cout << '\n';
    for (int i = 0; i < 4; i++) {
        std::cout << y_points[i] << " ";
    }
}

int main() {
    TestTranslate();
    std::cout << "________" << '\n';
    TestRotate();
    return 0;
}

#include "transform.h"
#include <cmath>
#include <iostream>

void TestTranslate() {
    double x[4] = {1.0, 2.0, 3.0, 4.0};
    double y[4] = {5.0, 6.0, 7.0, 8.0};
    TranslateI64_intrin(x, y, -2, 8);
    for (int i = 0; i < 4; i++) {
        std::cout << x[i] << " ";
    }
    std::cout << '\n';
    for (int i = 0; i < 4; i++) {
        std::cout << y[i] << " ";
    }
    std::cout << '\n';
}

void TestRotate() {
    double x_points[4] = {1.0, 2.0, 3.0, 4.0};
    double y_points[4] = {1.0, 2.0, 3.0, 4.0};
    double angle = M_PI / 2;
    RotateI64_intrin(x_points, y_points, angle);
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
    std::cout << "-----------------" << '\n';
//    TestRotate();
    return 0;
}

#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include "Point.h"
#include "my_math.h"

class Camera {
public:
    struct Resolution {
        size_t x = 10;
        size_t y = 10;
    };
    struct Size {
        double x = 10;
        double y = 10;
    };
    

    Point position = {0, 0, 0};
    Point direction = {1, 1, 1};
    Resolution resolution = {10, 10};
    Size size = {10, 10};
    

    Camera(Point p = {0, 0, 0}, Point d = {1, 1, 1}, Resolution r = {10, 10}, Size s = {10, 10}) : 
        position(p), direction(d), resolution(r), size(s) {}

    Point pixel_point(size_t i, size_t j) const {
        double A{direction.x}, B{direction.y}, C{direction.z};
        double sq = std::sqrt(C*C + A*A + B*B);
        double cos_1{A/sq}, cos_2{B/sq}, cos_3{C/sq};
        double a{std::acos(cos_1)}, b{std::acos(cos_2)}, c{std::acos(cos_3)};
        double sin_1{sin(a)}, sin_2{sin(b)}, sin_3{sin(c)};

        std::array<double, 3> line1 = {cos_2*cos_3, -sin_3*cos_2, sin_2};

        double a21 = sin_1*sin_2*cos_3+sin_3*cos_1;
        double a22 = -sin_1*sin_2*sin_3+cos_3*cos_1;
        double a23 = -sin_1*cos_2;
        std::array<double, 3> line2 = {a21, a22, a23};

        std::array<double, 3> line3 = {sin_1*sin_3-sin_2*cos_1*cos_3, sin_1*cos_3+sin_2*sin_3*cos_1, cos_1*cos_2};

        std::array<std::array<double, 3>, 3> M = {
            line1,
            line2,
            line3
        };
        // пока что у нас камера смотрит вдоль оси y
        // надо использовать матрицы вращения для определения и углы, выведенные из вектора нормали
        Point p = Point({size.x*i/resolution.x, 0, size.y*j/resolution.y});
        std::array<double, 3> line = M_x(M, {p.x, p.y, p.z});
        p = {line[0], line[1], line[2]};

        return position + p;
    }
};

#endif // CAMERA_CLASS_H
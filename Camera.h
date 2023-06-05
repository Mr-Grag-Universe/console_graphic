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
    double angle = 0;
    

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

        cos_3 = -std::sqrt(position.x*position.x + position.y*position.y)/position.r();
        cos_1 = position.x/(position.r()*cos_3);
        sin_3 = std::sin(std::acos(cos_3));
        sin_1 = std::sin(std::acos(cos_1));

        std::array<std::array<double, 3>, 3> M = {
            line1,
            line2,
            line3
        };
        // пока что у нас камера смотрит вдоль оси y
        // надо использовать матрицы вращения для определения и углы, выведенные из вектора нормали
        int x = (int)j-(int)resolution.x/2;
        int y = (int)i-(int)resolution.y/2;
        Point p = Point({size.x * (double)x/(double)resolution.x, 0, size.y*(double)y/(double)resolution.y});
        p = Point({0, position.r(), 0}) + p;
        line1 = {   1,    0,      0       };
        line2 = {   0,    cos_3,  -sin_3  };
        line3 = {   0,    sin_3,  cos_3   };
        std::array<std::array<double, 3>, 3> M1 = {
            line1,
            line2,
            line3
        };
        line1 = {cos_1, -sin_1, 0};
        line2 = {sin_1, cos_1, 0};
        line3 = {0, 0, 1};
        std::array<std::array<double, 3>, 3> M2 = {
            line1,
            line2,
            line3
        };
        std::array<double, 3> line = M_x(M1, {p.x, p.y, p.z});
        line = M_x(M2, line);
        p = {line[0], line[1], line[2]};

        return p;
    }

    Point pixel_direction(size_t i, size_t j) const {
        // считаем вектор высоты из точки до плоскости камеры
        double tan_ax = std::tan(angle/2);
        double h = (tan_ax < 0.00000001) ? -1 : size.x / tan_ax;
        if (h < 0)
            return direction;
        // Point d = direction * (h / direction.r());

        double cos_3 = -std::sqrt(position.x*position.x + position.y*position.y)/position.r();
        double cos_1 = position.x/(position.r()*cos_3);
        double sin_3 = std::sin(std::acos(cos_3));
        double sin_1 = std::sin(std::acos(cos_1));

        int x = (int)j-(int)resolution.x/2;
        int y = (int)i-(int)resolution.y/2;
        Point p = Point({size.x * (double)x/(double)resolution.x, 0, size.y*(double)y/(double)resolution.y});
        Point d = Point({0, h, 0});

        p = Point({0, position.r(), 0}) + p;
        d = Point({0, position.r(), 0}) + d;

        std::array<double, 3> line1 = {   1,    0,      0       };
        std::array<double, 3> line2 = {   0,    cos_3,  -sin_3  };
        std::array<double, 3> line3 = {   0,    sin_3,  cos_3   };
        std::array<std::array<double, 3>, 3> M1 = {
            line1,
            line2,
            line3
        };
        line1 = {cos_1, -sin_1, 0};
        line2 = {sin_1, cos_1, 0};
        line3 = {0, 0, 1};
        std::array<std::array<double, 3>, 3> M2 = {
            line1,
            line2,
            line3
        };

        std::array<double, 3> line = M_x(M1, {p.x, p.y, p.z});
        line = M_x(M2, line);
        p = {line[0], line[1], line[2]};

        line = M_x(M1, {d.x, d.y, d.z});
        line = M_x(M2, line);
        d = {line[0], line[1], line[2]};

        return p-d;
    }

    std::vector<std::vector<Point>> grid() const {
        std::vector<std::vector<Point>> g(size.y);
        for (size_t i = 0; i < size.y; ++i) {
            g[i] = std::vector<Point>(size.x);
            for (size_t j = 0; j < size.x; ++j) {
                g[i][j] = this->pixel_point(i, j);
            }
        }
        return g;
    }

    void move(Point p) {
        this->position += p;
    }

    void resize(double x, double y) {
        size.x = x;
        size.y = y;
    }

    void set_angle(double a) {
        if (a < 0 || a > M_PI) {
            throw std::runtime_error("bad angle");
        }
        angle = a;
    }
};

#endif // CAMERA_CLASS_H
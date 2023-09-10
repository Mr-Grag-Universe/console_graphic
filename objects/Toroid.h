#ifndef TOROID_CLASS_H
#define TOROID_CLASS_H

#include "../Object.h"

class Toroid : public Object {
public:
    Toroid() = delete;

    Toroid(Object && o) : Object(o) {}

    static Toroid Create(size_t n, double R, double r) {
        if (r > R) {
            throw std::runtime_error("we cannot create such toroid");
        }
        double alpha = M_PI*2 / n;
        size_t k = (size_t) M_PI / std::asin(R * std::sin(M_PI/n) / 2) + 1;
        if (k < 3) {
            std::cout << "too small k" << std::endl;
            throw std::runtime_error("too small k");
        }
        double betta = M_PI*2 / k;
        std::vector<point_ptr> circle(k);
        std::vector<point_ptr> points;
        Point center = {R+r, 0, 0};
        for (size_t i = 0; i < k; ++i) {
            circle[i] = std::make_shared<Point>(Point({R+r*std::cos(betta*i), 0, r*std::sin(betta*i)}));
        }
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < k; ++j) {
                Point p = *(circle[j]);
                double x = p.x * std::cos(alpha*i) - p.y * std::sin(alpha*i);
                double y = p.x * std::sin(alpha*i) + p.y * std::cos(alpha*i);
                p = {x, y, p.z};

                points.push_back(std::make_shared<Point>(p));
            }
        }

        std::vector<Triangle> faces;
        // теперь натягиваем треугольники на точки
        for (size_t i = 0; i < n; ++i) {
            // индексы первого и второго кольца
            size_t ind_c1 = i;
            size_t ind_c2 = (i+1) % n;

            for (size_t j = 0; j < k; ++j) {
                size_t ind_p1 = j;
                size_t ind_p2 = (j+1) % k;

                auto p00{ points[ind_c1*k + ind_p1] };
                auto p01{ points[ind_c1*k + ind_p2] };
                auto p10{ points[ind_c2*k + ind_p1] };
                auto p11{ points[ind_c2*k + ind_p2] };

                faces.push_back({p00, p01, p10});
                faces.push_back({p11, p01, p10});
            }
        }

        auto o = Object(ClosedPolyhedron(Polyhedron(faces)));
        return Toroid(std::move(o));
    }
};

#endif // TOROID_CLASS_H
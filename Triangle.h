#ifndef TRIANGLE_CLASS_H
#define TRIANGLE_CLASS_H

#include <array>

#include "Point.h"

class Triangle {
    std::array <Point, 3> v;
public:
    Triangle(std::array <Point, 3> p) : v(p) {}

    double S() {
        return (std::abs(((v[0]-v[2]) ^ (v[1]-v[2])).r()) / 2);
    }


};

#endif // TRIANGLE_CLASS_H
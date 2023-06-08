#ifndef VECTOR_CLASS_H
#define VECTOR_CLASS_H

#include "Point.h"

class Vector {
public:
    Point start;
    Point end;

    Vector(Point p1, Point p2={0, 0, 0}) : start(p1), end(p2) {}

    void reverse() {
        std::swap(start, end);
    }

    double magnitude() {
        return (end - start).r();
    }

    double scalar(const Vector & v) const {
        return start.x*v.start.x + start.y*v.start.y + start.y*v.start.y;
    }

    Vector friend operator*(double x, const Vector & v) {
        Vector res = Vector(v);
        return res;
    }
};

#endif // VECTOR_CLASS_H
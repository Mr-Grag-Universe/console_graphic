#ifndef POINT_CLASS_H
#define POINT_CLASS_H

#include <cmath>

class Point {
public:
    double x{}, y{}, z{};

    Point() {}
    Point(double x, double y, double z) : x(x), y(y), z(z) {}
    Point(std::initializer_list<double> l) {
        x = l.begin()[0];
        y = l.begin()[1];
        z = l.begin()[2];
        
    }

    void move(double x, double y, double z) {
        this->x += x;
        this->y += y;
        this->z += z;
    }

    double r() const {
        return std::sqrt(x*x + y*y + z*z);
    }

    double scalar(const Point & p) const {
        return x*p.x + y*p.y + z*p.z;
    }

    Point operator-(const Point & p) const {
        return Point(x-p.x, y-p.y, z-p.z);
    }
    Point operator+(const Point & p) const {
        return Point(x+p.x, y+p.y, z+p.z);
    }

    double operator*(const Point & p) const {
        return x*p.x + y*p.y + z*p.z;
    }
    Point operator*(double a) const {
        return Point(x*a, y*a, z*a);
    }
    Point friend operator*(double a, const Point & p) {
        Point P = p;
        P.x *= a;
        P.y *= a;
        P.z *= a;
        return P;
    }

    Point operator/(double a) {
        return *this * (1/a);
    }

    Point operator^(const Point & p) const {
        return Point(y*p.z - p.y*z, -x*p.z + p.x*z, x*p.y - y*p.x);
    }

    double angle(const Point & p) const {
        return std::acos(p*(*this) / (this->r() * p.r()));
    }
    double cos(const Point & p) const {
        return p*(*this) / (this->r() * p.r());
    }
    double sin(const Point & p) const {
        return std::sin(std::acos(p*(*this) / (this->r() * p.r())));
    }
    double tan(const Point & p) const {
        return std::tan(std::acos(p*(*this) / (this->r() * p.r())));
    }

    bool operator==(const Point & p) const {
        return (x == p.x) && (y == p.y) && (z == p.z);
    }
    bool operator<(const Point & p) const {
        return (x < p.x) && (y < p.y) && (z < p.z);
    }
};

#endif
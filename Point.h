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
    bool operator!=(const Point & p) const {
        return (x != p.x) || (y != p.y) || (z != p.z);
    }
    bool operator<(const Point & p) const {
        if (this->r() < p.r()) {
            return true;
        } else if (this->r() > p.r()) {
            return false;
        } else if (x < p.x) {
            return true;
        } else if (x != p.x) {
            return false;
        } else if (y < p.y) {
            return true;
        } else if (y != p.y) {
            return false;
        }
        return (z < p.z);
    }

    Point orto_r() const {
        if (x*y*z)
            return {1/x, -1/y, 0};

        if (x == 0 && y == 0 && z == 0)
            return {1, 0, 0};

        if (x) {
            if (y) {
                return {1/x, -1/y, 0};
            } else if (z) {
                return {1/x, 0, -1/z};
            } else {
                return {0, 1, 1};
            }
        } else if (y) {
            if (z) {
                return {1, -1/y, 1/z};
            } else {
                return {1, 0, 1};
            }
        } else {
            return {1, 1, 0};
        }
    }
};

#include <memory>
using point_ptr = std::shared_ptr<Point>;

#endif
#ifndef TRIANGLE_CLASS_H
#define TRIANGLE_CLASS_H

#include <array>
#include <set>
#include <vector>
#include <map>
#include <memory>

#include <algorithm>
#include <utility>

#include "Point.h"
#include "Section.h"



class Triangle {
    std::array <point_ptr, 3> v;
    std::map <std::pair<int, int>, Section> e; // edges

    #define EPS 1e-10

    static double triangle_square(double a,double b, double c) {
        double p=(a+b+c)/2;
        return sqrt(p*(p-a)*(p-b)*(p-c));
    }
    static bool inside_triangle(double P_x,double P_y, double P_z, double A_x, double A_y, double A_z, double B_x, double B_y, double B_z, double C_x, double C_y, double C_z){
        int inside=0;
        double AB=sqrt( (A_x-B_x)*(A_x-B_x) + (A_y-B_y)*(A_y-B_y) + (A_z-B_z)*(A_z-B_z) );
        double BC=sqrt( (B_x-C_x)*(B_x-C_x) + (B_y-C_y)*(B_y-C_y) + (B_z-C_z)*(B_z-C_z) );
        double CA=sqrt( (A_x-C_x)*(A_x-C_x) + (A_y-C_y)*(A_y-C_y) + (A_z-C_z)*(A_z-C_z) );

        double AP=sqrt( (P_x-A_x)*(P_x-A_x) + (P_y-A_y)*(P_y-A_y) + (P_z-A_z)*(P_z-A_z) );
        double BP=sqrt( (P_x-B_x)*(P_x-B_x) + (P_y-B_y)*(P_y-B_y) + (P_z-B_z)*(P_z-B_z) );
        double CP=sqrt( (P_x-C_x)*(P_x-C_x) + (P_y-C_y)*(P_y-C_y) + (P_z-C_z)*(P_z-C_z) );
        double diff=(triangle_square(AP,BP,AB)+triangle_square(AP,CP,CA)+triangle_square(BP,CP,BC))-triangle_square(AB,BC,CA);
                if (fabs(diff)<EPS) inside=1;
        return inside;
    }
public:
    Triangle(std::array <point_ptr, 3> p) : v(p) {
        e[std::make_pair(0, 2)] = Section(p[0], p[2]);
        e[std::make_pair(0, 1)] = Section(p[0], p[1]);
        e[std::make_pair(1, 2)] = Section(p[1], p[2]);
    }
    Triangle(std::initializer_list<point_ptr> p) : v({p.begin()[0], p.begin()[1], p.begin()[2]}) {
        e[std::make_pair(0, 2)] = Section(v[0], v[2]);
        e[std::make_pair(0, 1)] = Section(v[0], v[1]);
        e[std::make_pair(1, 2)] = Section(v[1], v[2]);
    }

    bool operator<(const Triangle & t) const {
        if (this->S() < t.S()) {
            return true;
        } else if (this->S() != t.S()) {
            return false;
        }
        std::vector <point_ptr> v1 = {v[0], v[1], v[2]};
        auto v2 = t.get_v();
        // Point v2[3] = {V[0], V[1], V[2]};
        std::sort(v1.begin(), v1.end(), [](const point_ptr & x, const point_ptr & y){ return *x < *y; });
        std::sort(v2.begin(), v2.end(), [](const point_ptr & x, const point_ptr & y){ return *x < *y; });
        if (v1 == v2) {
            return false;
        }
        if (*(v1[2]) < *(v2[2])) {
            return true;
        } else if (*(v1[2]) != *(v2[2])) {
            return false;
        } else if (*(v1[1]) < *(v2[1])) {
            return true;
        } else if (*(v1[1]) != *(v2[1])) {
            return false;
        }
        return *(v1[0]) < *(v2[0]);
    }

    bool operator==(const Triangle & t) const {
        std::set <Point> s1 = {*(v[0]), *(v[1]), *(v[2])};
        // s1.insert(v.begin(), v.begin());
        auto t_v = t.get_v();
        std::set <Point> s2 = {*(t_v[0]), *(t_v[1]), *(t_v[2])};
        return s1 == s2;
    }

    double S() const {
        return (std::abs(((*(v[0])-*(v[2])) ^ (*(v[1])-*(v[2]))).r()) / 2);
    }

    std::array<double, 4> coeffs() const {
        Point n = this->normal();
        double d = -(n.x*(*(v[0])).x + n.y*(*(v[0])).y + n.z*(*(v[0])).z);
        return {n.x, n.y, n.z, d};
    }

    Point center() const {
        double x{}, y{}, z{};
        for (auto & v : v) {
            x += v->x;
            y += v->y;
            z += v->z;
        }
        x /= 3;
        y /= 3;
        z /= 3;
        return {x, y, z};
    }

    Point normal() const {
        Point p = (*(v[0])-*(v[1])) ^ (*(v[0])-*(v[2]));
        return (p / p.r()) * (p.cos(*(v[0])) >= 0 ? 1 : -1); // нормаль направлена от начала координат
    }

    double distance(Point && p) const {
        // normal vector
        Point n = this->normal();
        double d = -(n.x*(*(v[0])).x + n.y*(*(v[0])).y + n.z*(*(v[0])).z);
        double num = std::abs(n.x*p.x + n.y*p.y + n.z*p.z + d);
        double del = std::sqrt(n.x*n.x + n.y*n.y + n.z*n.z);
        return num/del;
    }
    double distance(Point p) const {
        // normal vector
        Point n = this->normal();
        double d = -(n.x*(*(v[0])).x + n.y*(*(v[0])).y + n.z*(*(v[0])).z);
        double num = std::abs(n.x*p.x + n.y*p.y + n.z*p.z + d);
        double del = std::sqrt(n.x*n.x + n.y*n.y + n.z*n.z);
        return num/del;
    }


    bool belong_to_plane(Point p) const {
        Point n = this->normal();
        double d = -(n.x*(*(v[0])).x + n.y*(*(v[0])).y + n.z*(*(v[0])).z);
        return (p.x*n.x + p.y*n.y + p.z*n.z + d) == 0;
    }

    Point projection(Point p) const {
        double d = this->distance(p);
        Point n = this->normal() * d;
        Point p1{p + n}, p2{p - n};
        if (this->belong_to_plane(p1))
            return p1;
        return p2;
    }

    bool on_triangle(Point p) const {
        return inside_triangle(v[0]->x, v[0]->y, v[0]->z, v[1]->x, v[1]->y, v[1]->z, v[2]->x, v[2]->y, v[2]->z, p.x, p.y, p.z);
    }

    bool projection_on_triangle(Point p) const {
        p = this->projection(p);
        return this->on_triangle(p);
    }

    // p - точка, через которую проходит
    // v - направляющий вектор
    bool parallel(Point p, Point l) const {
        double d = this->distance(p);
        double dd = (this->projection(p+l)-(p+l)).r();
        return std::abs(dd - d) < std::pow(10, -10);
    }

    Point cross_point(Point p, Point l) const {
        if (parallel(p, l)) {
            throw std::runtime_error("this line and pale are parallel");
        }

        auto coef = this->coeffs();
        double x{v[0]->x}, y(v[0]->y), z(v[0]->z);
        double A{coef[0]}, B{coef[1]}, C{coef[2]}, D{coef[3]};
        double t = -(A*p.x + B*p.y + C*p.z + D) / (A*l.x+B*l.y+C*l.z);
        return {l.x*t+p.x, l.y*t+p.y, l.z*t+p.z};
    }

    bool cross_triangle(Point p, Point l) const {
        Point pp = this->cross_point(p, l);
        return this->on_triangle(pp);
    }

    // ================= getters ================ //
    std::vector <point_ptr> get_v() const {
        std::vector<point_ptr> res(v.begin(), v.end());
        return res;
    }
    std::vector <Section> get_e() const {
        std::vector<Section> res;
        for (auto & el : e) {
            res.emplace_back(el.second);
        }
        return res;
    }
};

#endif // TRIANGLE_CLASS_H
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

    Point normal() {
        Point p = (*(v[0])-*(v[1])) ^ (*(v[0])-*(v[2]));
        return (p / p.r()) * (p.cos(*(v[0])) >= 0 ? 1 : -1); // нормаль направлена от начала координат
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
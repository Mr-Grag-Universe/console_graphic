#ifndef TRIANGLE_CLASS_H
#define TRIANGLE_CLASS_H

#include <array>
#include <set>
#include <vector>
#include <map>

#include <algorithm>

#include "Point.h"
#include "Section.h"



class Triangle {
    std::array <Point, 3> v;
    std::map <std::pair<int, int>, Section> e; // edges
public:
    Triangle(std::array <Point, 3> p) : v(p) {
        e[std::make_pair(0, 2)] = Section(p[0], p[2]);
        e[std::make_pair(0, 1)] = Section(p[0], p[1]);
        e[std::make_pair(1, 2)] = Section(p[1], p[2]);
    }
    Triangle(std::initializer_list<Point> p) : v({p.begin()[0], p.begin()[1], p.begin()[2]}) {
        e[std::make_pair(0, 2)] = Section(v[0], v[2]);
        e[std::make_pair(0, 1)] = Section(v[0], v[1]);
        e[std::make_pair(1, 2)] = Section(v[1], v[2]);
    }

    bool operator<(const Triangle & t) const {
        return this->S() < t.S();
    }

    bool operator==(const Triangle & t) const {
        std::set <Point> s1 = {};
        s1.insert(v.begin(), v.begin());
        std::set <Point> s2 = {};
        s2.insert(t.get_v().begin(), t.get_v().begin());

        return s1 == s2;
    }

    double S() const {
        return (std::abs(((v[0]-v[2]) ^ (v[1]-v[2])).r()) / 2);
    }

    Point center() const {
        double x{}, y{}, z{};
        for (auto & v : v) {
            x += v.x;
            y += v.y;
            z += v.z;
        }
        x /= 3;
        y /= 3;
        z /= 3;
        return {x, y, z};
    }

    Point normal() {
        Point p = (v[0]-v[1]) ^ (v[0]-v[2]);
        return (p / p.r()) * (p.cos(v[0]) >= 0 ? 1 : -1); // нормаль направлена от начала координат
    }

    // ================= getters ================ //
    std::vector <Point> get_v() const {
        std::vector<Point> res(v.begin(), v.end());
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
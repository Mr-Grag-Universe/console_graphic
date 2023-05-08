#ifndef SECTION_CLASS_H
#define SECTION_CLASS_H

#include <array>

#include "Point.h"

class Section {
public:
    Point v1, v0;

    Section() = default;
    Section(const Point & p1, const Point & p2) : v0(p1), v1(p2) {}
    Section(std::pair<Point, Point> p) : v0(p.first), v1(p.second) {}

    Section(const Section & s) = default;

    bool operator==(const Section & s) {
        return (s.v0 == v0  && s.v1 == v1) || (s.v0 == v1  && s.v1 == v0);
    }

    bool operator<(const Section & s) const {
        return this->len() < s.len();
    }

    double len() const {
        return (v0-v1).r();
    }
};

#endif // SECTION_CLASS_H
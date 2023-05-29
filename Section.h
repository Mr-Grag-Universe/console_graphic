#ifndef SECTION_CLASS_H
#define SECTION_CLASS_H

#include <array>
#include <memory>

#include "Point.h"

class Section {
public:
    point_ptr v1, v0;

    Section() = default;
    Section(const point_ptr p1, const point_ptr p2) : v0(p1), v1(p2) {}
    Section(std::pair<point_ptr, point_ptr> p) : v0(p.first), v1(p.second) {}

    Section(const Section & s) = default;

    bool operator==(const Section & s) {
        return (*(s.v0) == *v0  && *(s.v1) == *v1) || (*(s.v0) == *v1  && *(s.v1) == *v0);
    }

    bool operator<(const Section & s) const {
        if (this->len() < s.len()) {
            return true;
        } else if (this->len() != s.len()) {
            return false;
        } else if (!(*v0 == *(s.v0)) && (*v1 == *(s.v1)) || *v0 == *(s.v1) && *v1 == *(s.v0)) {
            return false;
        } else if (*v0 < *(s.v0)) {
            return true;
        } else if (*v0 != *(s.v0)) {
            return false;
        }
        return (*v1 < *(s.v1));
    }

    double len() const {
        return (*v0-*v1).r();
    }
};

#endif // SECTION_CLASS_H
#ifndef CLOSED_POLYGON_CLASS_H
#define CLOSED_POLYGON_CLASS_H

#include "Polyhedron.h"
#include "Section.h"
#include <string>

class ClosedPolygon : Polyhedron {
private:
public:

    ClosedPolygon(const Polyhedron & p) {
        if (p.closed()) {
            e = p.get_e();
            v = p.get_v();
            f = p.get_f();
        } else {
            throw std::string("this is not closed polyhedron");
        }
    }
};

#endif // CLOSED_POLYGON_CLASS_H
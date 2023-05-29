#ifndef CLOSED_POLYHEDRON_CLASS_H
#define CLOSED_POLYHEDRON_CLASS_H

#include "Polyhedron.h"
#include "Section.h"
#include <string>

class ClosedPolyhedron : Polyhedron {
private:
public:

    ClosedPolyhedron(const Polyhedron & p) {
        if (p.closed()) {
            e = p.get_e();
            v = p.get_v();
            f = p.get_f();
        } else {
            throw std::string("this is not closed polyhedron");
        }
    }
};

#endif // CLOSED_POLYHEDRON_CLASS_H
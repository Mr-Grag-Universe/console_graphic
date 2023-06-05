#ifndef CUBE_CLASS_H
#define CUBE_CLASS_H

#include "../Object.h"

class Cube : public Object {
public:
    Cube() = delete;

    Cube(Object & o) : Object(o) {}

    static Cube CreateDefault(){
        auto p000 = std::make_shared<Point>(Point({0, 0, 0}));
        auto p001 = std::make_shared<Point>(Point({0, 0, 1}));
        auto p010 = std::make_shared<Point>(Point({0, 1, 0}));
        auto p011 = std::make_shared<Point>(Point({0, 1, 1}));
        auto p100 = std::make_shared<Point>(Point({1, 0, 0}));
        auto p101 = std::make_shared<Point>(Point({1, 0, 1}));
        auto p110 = std::make_shared<Point>(Point({1, 1, 0}));
        auto p111 = std::make_shared<Point>(Point({1, 1, 1}));

        auto o = Object(ClosedPolyhedron(Polyhedron(
        {
            Triangle({p000, p010, p100}),
            Triangle({p110, p010, p100}),

            Triangle({p001, p011, p101}),
            Triangle({p111, p011, p101}),

            Triangle({p000, p100, p001}),
            Triangle({p101, p100, p001}),

            Triangle({p000, p010, p001}),
            Triangle({p011, p010, p001}),

            Triangle({p110, p100, p111}),
            Triangle({p101, p100, p111}),

            Triangle({p110, p010, p111}),
            Triangle({p011, p010, p111}),
        })));
        return Cube(o);
    }
};

#endif // CUBE_CLASS_H
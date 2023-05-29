#ifndef OBJECT_CLASS_H
#define OBJECT_CLASS_H

#include "ClosedPolyhedron.h"

class Object : ClosedPolyhedron {
public:
    Object() : ClosedPolyhedron({
        {{1, 0, 0}, {0, 0, 0}, {0, 1, 0}}, 
        {{0, 0, 0}, {1, 0, 0}, {0, 0, 1}},
        {{0, 0, 0}, {0, 1, 0}, {0, 0, 1}}, 
        {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}
    }) {

    }
};

#endif // OBJECT_CLASS_H
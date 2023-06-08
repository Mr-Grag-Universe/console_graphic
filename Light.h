#ifndef LIGHT_CLASS_H
#define LIGHT_CLASS_H

#include "Geometry/geometry.h"

class LightSrc {
public:
    Point position = {0, 0, 0};

    virtual ~LightSrc() = default;
    virtual Point _point() const { return {0, 0, 0}; }
};

#endif // LIGHT_CLASS_H
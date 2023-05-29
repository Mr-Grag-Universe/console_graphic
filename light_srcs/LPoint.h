#ifndef LPOINT_CLASS_H
#define LPOINT_CLASS_H

#include "../Point.h"
#include "../Light.h"

class LPoint : public LightSrc {
public:
    double power = 10;
    point_ptr point;

    LPoint(Point p={0,0,0}, double pow=0) : point(std::make_shared<Point>(p)), power(pow) {}
    LPoint(point_ptr pp, double pow=0) : point(pp), power(pow) {}
    ~LPoint() = default;

    virtual Point _point() const {
        return *point;
    }
};

#endif // LPOINT_CLASS_H
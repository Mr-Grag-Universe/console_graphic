#ifndef LPOINT_CLASS_H
#define LPOINT_CLASS_H

#include "../Point.h"
#include "../Light.h"

class LPoint : public LightSrc {
public:
    double power = 10;

    LPoint(const Point & p, double pow=0) : power(pow) {
        position = p;
    }
    LPoint(Point && pp, double pow=0) : power(pow) {
        position = pp;
    }
    ~LPoint() = default;

    virtual Point _point() const {
        return position;
    }
};

#endif // LPOINT_CLASS_H
#ifndef TETRAIDER_CLASS_H
#define TETRAIDER_CLASS_H

#include "../Object.h"

class Tetraider : public Object {
public:
    Tetraider() : Object(Object::CreateDefault()) {}

    virtual double volume() const override {
        Triangle t = *(f.begin());
        auto points = t.get_v();
        Point point;
        for (auto & p : v) {
            if (std::find_if(points.begin(), points.end(), [p](const auto & pp){ return *pp == *p; }) == points.end()) {
                point = *p;
                break;
            }
        }

        return t.S()*t.distance(std::move(point))/2;
    }
};

#endif // TETRAIDER_CLASS_H
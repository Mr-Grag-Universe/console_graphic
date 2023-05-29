#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include "Point.h"

class Camera {
public:
    struct Resolution {
        size_t x = 10;
        size_t y = 10;
    };
    struct Size {
        size_t x = 10;
        size_t y = 10;
    };
    

    Point position = {0, 0, 0};
    Point direction = {1, 1, 1};
    Resolution resolution = {10, 10};
    Size size = {10, 10};
    

    Camera(Point p = {0, 0, 0}, Point d = {1, 1, 1}, Resolution r = {10, 10}, Size s = {10, 10}) : 
        position(p), direction(d), resolution(r), size(s) {}
};

#endif // CAMERA_CLASS_H
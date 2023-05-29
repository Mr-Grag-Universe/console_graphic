#ifndef LIGHT_CLASS_H
#define LIGHT_CLASS_H

class LightSrc {
public:
    virtual ~LightSrc() = default;
    virtual Point _point() const { return {0, 0, 0}; }
};

#endif // LIGHT_CLASS_H
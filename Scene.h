#ifndef SCENE_CLASS_H
#define SCENE_CLASS_H

#include <vector>
#include <set>
#include <algorithm>
#include <memory>
#include "Object.h"
#include "Light.h"


class Scene {
    std::vector<std::shared_ptr<Object>> objects;
    std::vector<std::shared_ptr<LightSrc>> lights;
public:

};

#endif // SCENE_CLASS_H
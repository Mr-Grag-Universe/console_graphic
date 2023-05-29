#ifndef SCENE_CLASS_H
#define SCENE_CLASS_H

#include <vector>
#include <set>
#include <algorithm>
#include <memory>
#include "Object.h"
#include "Light.h"
#include "Camera.h"
#include "light_srcs/LPoint.h"
#include "objects/Tetraider.h"


class Scene {
    std::vector<std::shared_ptr<Object>> objects = {std::make_shared<Tetraider>()};
    std::vector<std::shared_ptr<LightSrc>> lights = {std::make_shared<LPoint>(LPoint({10, 10, 10}))};
    std::vector<std::shared_ptr<Camera>> cameras = {std::make_shared<Camera>(Camera({0, 10, 5}, {-1, -1, -1}, {100, 100}))};
public:
    Scene() {}

    /// @brief create nice for next rendering map of light intensity
    /// @param ind - camera for working with
    /// @return matrix of light intensity for rendering 
    std::vector <std::vector<double>> take_look(size_t ind=0) const {
        Camera::Resolution resolution = cameras[ind]->resolution;
        std::vector <std::vector<double>> picture(resolution.y);

        for (size_t i = 0; i < picture.size(); ++i) {
            std::vector<double> & line = picture[i];
            line = std::vector<double>(resolution.x);
            for (size_t j = 0; j < line.size(); ++j) {
                double & pixel = line[j];

                // process certain pixel
                
            }
        }
        return picture;
    }
};

#endif // SCENE_CLASS_H
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
#include "my_math.h"


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
        Camera & camera = *(cameras[ind]);
        Camera::Resolution resolution = camera.resolution;
        std::vector <std::vector<double>> picture(resolution.y);

        for (size_t i = 0; i < picture.size(); ++i) {
            std::vector<double> & line = picture[i];
            line = std::vector<double>(resolution.x);
            for (size_t j = 0; j < line.size(); ++j) {
                double & pixel = line[j];
                Point point = camera.pixel_point(i, j);

                // process certain pixel
                // пока тактика такая:
                // 1) узнаём, принадлежит ли основание высоты на все плоскости к треугильнику, задающему эту плоскость
                //    на основании чего делаем вывод, какие треугольника рассматриваем
                // 2) считаем кол-во треугольников с + и - косинусом векторов
                //      * приоритет в рамках одной фигуры отдаём ближайшей грани
                // 3) берём среднее от самой многочисленной группы

                std::vector<double> l = {};
                for (auto & o : objects) {
                    double m = -1;
                    for (auto & f : o->get_faces()) {
                        if (f.)
                    }
                }
            }
        }
        return picture;
    }
};

#endif // SCENE_CLASS_H
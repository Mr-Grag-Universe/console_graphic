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
    std::vector<std::shared_ptr<LightSrc>> lights = {std::make_shared<LPoint>(LPoint({5, 5, 5}))};
    std::vector<std::shared_ptr<Camera>> cameras = {std::make_shared<Camera>(Camera({8, 8, 8}, {-1, -1, -1}, {10, 10}, {10, 10}))};

    static double intensity(const Triangle & t, std::vector<std::shared_ptr<LightSrc>> lights) {
        // временное решение через точечные источники света
        // по хорошему надо для каждого конкретного источника свой способ подсчёта писать
        double sum = 0;
        for (auto & l : lights) {
            Point V = (t.projection(l->_point()) - l->_point());
            V = V * (1/V.r());
            sum += t.normal()*V;
        }
        return (sum+1)/2;
    }
public:
    Scene() {}

    /// @brief create nice for next rendering map of light intensity
    /// @param ind - camera for working with
    /// @return matrix of light intensity for rendering 
    std::vector <std::vector<double>> take_look(size_t ind=0) const {
        Camera & camera = *(cameras[ind]);

        auto grid = camera.grid();
        for (auto & line : grid) {
            for (auto & p : line) {
                std::cout << p << " ";
            }
            std::cout << std::endl;
        }

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
                // 3) ищем сумму / берём среднее от самой многочисленной группы

                // собираем освещённость
                std::vector<std::pair<double, double>> l = {};
                for (auto & o : objects) {
                    double m = std::pow(10, 20);
                    Triangle t = Triangle({std::make_shared<Point>(Point({0, 0, 0})), std::make_shared<Point>(Point({0, 0, 1})), std::make_shared<Point>(Point({0, 1, 0}))});
                    for (auto & f : o->get_faces()) {
                        bool err;
                        try {
                            err = f.cross_triangle(point, camera.direction);
                        } catch(...) {
                            continue;
                        }
                        if (err) {
                            double d = (f.cross_point(point, camera.direction) - point).r();
                            if (d < m) {
                                t = f;
                                m = d;
                            }
                        }
                    }
                    if (m != std::pow(10, 20)) {
                        double in = intensity(t, lights);
                        l.push_back(std::make_pair(in, m));
                    }
                }

                // считаем среднее
                double sum = 0;
                for (auto & el : l)
                    sum += el.first / std::pow(el.second, 2);

                pixel = sum;
            }
        }
        return picture;
    }
};

#endif // SCENE_CLASS_H
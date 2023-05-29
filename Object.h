#ifndef OBJECT_CLASS_H
#define OBJECT_CLASS_H

#include <memory>

#include "ClosedPolyhedron.h"

class Object : public ClosedPolyhedron {
public:
    // там проблема с инициализацией общих точек для объектов выше
    Object() = delete;

    /// @brief default constructor for object
    /// @return returns Object = tetraider
    static Object CreateDefault() {
        std::vector<point_ptr> points = {
            std::make_shared<Point>(Point(0,0,0)),
            std::make_shared<Point>(Point(1,0,0)),
            std::make_shared<Point>(Point(0,1,0)),
            std::make_shared<Point>(Point(0,0,1)),
            std::make_shared<Point>(Point(1,1,0)),
            std::make_shared<Point>(Point(1,0,1)),
            std::make_shared<Point>(Point(0,1,1)),
            std::make_shared<Point>(Point(1,1,1))
        };

        return Object(
            ClosedPolyhedron(
                Polyhedron(
                    {
                        { points[0], points[1], points[2] },
                        { points[1], points[3], points[0] },
                        { points[2], points[3], points[0] },
                        { points[1], points[3], points[2] },
                    }
                )
            )
        );
    }

    Object(ClosedPolyhedron & cp) : ClosedPolyhedron(cp) {}
    Object(ClosedPolyhedron && cp) : ClosedPolyhedron(cp) {}

    virtual std::set<Triangle> get_faces() {
        return f;
    }
};

#endif // OBJECT_CLASS_H
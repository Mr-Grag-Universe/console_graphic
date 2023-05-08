#ifndef POLYHEDRON_CLASS_H
#define POLYHEDRON_CLASS_H

#include <vector>
#include <set>
#include <stack>

#include "Point.h"
#include "Triangle.h"
#include "Section.h"

class Polyhedron {
public:
    std::set <Point> v = {};         // vertexes
    std::set <Triangle> f = {};      // faces
    std::set <Section> e = {};         // edges

    Polyhedron() {}
    Polyhedron(Point p) : v({p}) {}
    Polyhedron(Triangle t) {
        f.insert(t);
        std::vector<Point> V = t.get_v();
        v.insert(V.begin(), V.end());
        std::vector<Section> E = t.get_e();
        e.insert(E.begin(), E.end());
    }
    Polyhedron(std::initializer_list<Triangle> ts) {
        for (auto & t : ts) {
            f.insert(t);
            std::vector<Point> V = t.get_v();
            v.insert(V.begin(), V.end());
            std::vector<Section> E = t.get_e();
            e.insert(E.begin(), E.end());
        }
    }

    void add_point(const Point & p) {
        v.insert(p);
    }

    void add_face(Triangle t) {
        std::vector<Point> V = t.get_v();
        v.insert(V.begin(), V.end());
        f.emplace(t);
    }

    bool closed() const {
        // проверка заключается в том, чтобы пройтись по всем вершинам
        // и проверить, что каждая принадлежатъъит минимум 3 граням
        // и все грани имеют по 2 общих ребра с другими гранями

        for (auto & vertex : v) {
            std::set <Triangle> s = {};
            std::map <Point, int> m = {};
            for (auto & face : f) {
                std::vector <Point> a = face.get_v();
                auto it = std::find(a.begin(), a.end(), vertex);

                // если наша вершина принадлежит данной грани
                if (it != a.end()) {
                    a.erase(it);
                    s.insert(face);
                    try {
                        ++m.at(a[0]);
                    } catch (...) {
                        m[a[0]] = 1;
                    }
                    try {
                        ++m.at(a[1]);
                    } catch (...) {
                        m[a[1]] = 1;
                    }
                }
            }
            if (s.size() < 3)
                return 0;

            // нужно проверить, что ребра, не содержащие vertex образуют цикл (у всех степень больше 2)
            for (auto & el : m) {
                if (el.second < 2) {
                    return 0;
                }
            }
        }

        return 1;
    }

    // ============ getters ============ //
    std::set <Point>    get_v() const { return v; }
    std::set <Triangle> get_f() const { return f; }
    std::set <Section>  get_e() const { return e; }
};

#endif // POLYHEDRON_CLASS_H
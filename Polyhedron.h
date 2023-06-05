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
    std::set <point_ptr> v = {};         // vertexes
    std::set <Triangle> f = {};      // faces
    std::set <Section> e = {};         // edges

    Polyhedron() {}
    Polyhedron(point_ptr p) : v({p}) {}
    Polyhedron(Triangle t) {
        f.insert(t);
        std::vector<point_ptr> V = t.get_v();
        v.insert(V.begin(), V.end());
        std::vector<Section> E = t.get_e();
        e.insert(E.begin(), E.end());
    }
    Polyhedron(std::initializer_list<Triangle> ts) {
        for (auto t : ts) {
            f.insert(t);
            std::vector<point_ptr> V = t.get_v();
            for (auto el : V)
                v.insert(el);
            std::vector<Section> E = t.get_e();
            for (auto el : E)
                e.insert(el);
            e.insert(E.begin(), E.end());
        }
    }

    void add_point(const point_ptr p) {
        v.insert(p);
    }

    void add_face(Triangle t) {
        std::vector<point_ptr> V = t.get_v();
        v.insert(V.begin(), V.end());
        f.emplace(t);
    }

    bool closed() const {
        // проверка заключается в том, чтобы пройтись по всем вершинам
        // и проверить, что каждая принадлежатъъит минимум 3 граням
        // и все грани имеют по 2 общих ребра с другими гранями

        for (auto & vertex : v) {
            std::set <Triangle> s = {};
            std::map <point_ptr, int> m = {};
            for (auto & face : f) {
                std::vector <point_ptr> a = face.get_v();
                auto it = std::find_if(a.begin(), a.end(), [vertex](const point_ptr & p){ return *p == *vertex; });

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

    void sync() {
        std::map <Point, std::shared_ptr<Point>> points;
        for (auto & face : f) {
            auto vs = face.get_v();
            for (auto & v : vs) {
                points[*v] = v;
            }
        }

        for (auto & edge : e) {
            auto vs = edge.get_v();
            points[*(vs.first)] = vs.first;
            points[*(vs.second)] = vs.second;
        }

        for (Triangle face : f) {
            auto vs = face.get_v();
            face.set_v({points[*(vs[0])], points[*(vs[1])], points[*(vs[2])]});
        }

        for (auto & edge : e) {
            auto vs = edge.get_v();
            points[*(vs.first)] = vs.first;
            points[*(vs.second)] = vs.second;
        }
    }

    virtual void move(const Point & p) {
        for (auto & tr : v) {
            *tr += p;
        }
    }

    // ============ getters ============ //
    std::set <point_ptr>    get_v() const { return v; }
    std::set <Triangle>     get_f() const { return f; }
    std::set <Section>      get_e() const { return e; }
}; 

#endif // POLYHEDRON_CLASS_H
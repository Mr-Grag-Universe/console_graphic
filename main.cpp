#include <iostream>
#include <iomanip>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <thread>
#include <memory>
#include "atrib.h"
#include "Point.h"
#include "Triangle.h"
#include "Polyhedron.h"
#include "ClosedPolyhedron.h"
#include "Object.h"
#include "Scene.h"
#include "Render.h"

#define home()              printf(ESC "[H")
#define clrscr()            printf(ESC "[2J")
#define gotoxy(x, y)        printf(ESC "[%d;%dH", y, x);
#define visible_cursor()    printf(ESC "[?251");

#define resetcolor()        printf(ESC "[0m")
#define set_display_atrib(color)    printf(ESC "[%dm", color)

using namespace std::literals::chrono_literals;

void render() {

}


int main() {
    home();
	clrscr();
    // printf(ESC "\x1b]rgb:1/24/86");
    // printf("111");
    // return 0;

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	
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
    Triangle t = {points[0], points[1], points[2]};
    std::cout << t.S() << std::endl;

    Polyhedron p = {t};
    p.add_face({points[1], points[3], points[0]});
    p.add_face({points[2], points[3], points[0]});
    p.add_face({points[1], points[3], points[2]});
    try {
        ClosedPolyhedron cp(p);
    } catch (std::string s) {
        std::cout << s << std::endl;
    }

    try {
        Object o = Object::CreateDefault();
    } catch (...) {
        std::cout << "something came wrong" << std::endl;
    }

    Scene s = Scene();
    auto M = s.take_look();
    for (auto & line : M) {
        for (auto & el : line) {
            std::cout << std::setw(7) << std::left << std::fixed << std::setprecision(3)<< el << " | ";
        }
        std::cout << std::endl;
    }
    auto m = render_to_char(M);
    for (auto & line : m) {
        for (auto & el : line) {
            std::cout << std::setw(2) << std::internal << std::fixed << std::setprecision(3)<< el << " ";
        }
        std::cout << std::endl;
    }

    int ind = 0;
    s.cameras[0]->set_angle(M_PI/4);
    s.objects[0]->move({-10, 0, 0});
    s.objects.push_back(std::dynamic_pointer_cast<Object>(std::make_shared<Cube>(Cube::CreateDefault())));
    // s.cameras[0]->position = {10, 10, 10};
    while (true) {
        ++ind;
        clrscr();
        M = s.take_look();
        auto m = render_to_t_colors(M);
        for (size_t i = 0; i < m.size(); ++i) {
            auto line = m[i];
            for (size_t j = 0; j < line.size(); ++j) {
                auto & color = line[j];
                // std::cout << std::setw(4) << std::internal << std::fixed << std::setprecision(3)<< color << " ";
                gotoxy((int) j*2, (int) i);
                printf("\e[48;5;%dm .", color); //  set_display_atrib();
                // printf("#");
                resetcolor();
            }
            std::cout << std::endl;
        }
        s.cameras[0]->move({1, 1, 1});
        // s.cameras[0]->resize(1+ind, 1+ind);
        std::cout << s.cameras[0]->position << std::endl;
        std::this_thread::sleep_for(1s);
    }

	return 0;
}
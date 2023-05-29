#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <memory>
#include "atrib.h"
#include "Point.h"
#include "Triangle.h"
#include "Polyhedron.h"
#include "ClosedPolyhedron.h"
#include "Object.h"
#include "Scene.h"

#define home()              printf(ESC "[H")
#define clrscr()            printf(ESC "[2J")
#define gotoxy(x, y)        printf(ESC "[%d;%dH", y, x);
#define visible_cursor()    printf(ESC "[?251");

#define resetcolor()        printf(ESC "[0m")
#define set_display_atrib(color)    printf(ESC "[%dm", color)


void render() {

}


int main() {
    home();
	clrscr();

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

	return 0;
}
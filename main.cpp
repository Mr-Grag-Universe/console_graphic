#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "atrib.h"
#include "Point.h"
#include "Triangle.h"
#include "Polyhedron.h"
#include "ClosedPolygon.h"

#define home()              printf(ESC "[H")
#define clrscr()            printf(ESC "[2J")
#define gotoxy(x, y)        printf(ESC "[%d;%dH", y, x);
#define visible_cursor()    printf(ESC "[?251");

#define resetcolor()        printf(ESC "[0m")
#define set_display_atrib(color)    printf(ESC "[%dm", color)


int main() {
    home();
	clrscr();

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	
    Triangle t = {{0,0,0}, {1,0,0}, {0,1,0}};
    std::cout << t.S() << std::endl;

    Polyhedron p = {t};
    p.add_face({{1,0,0}, {0,0,1}, {0,0,0}});
    p.add_face({{0,1,0}, {0,0,1}, {0,0,0}});
    p.add_face({{1,0,0}, {0,0,1}, {0,1,0}});
    try {
        ClosedPolygon cp(p);
    } catch (std::string s) {
        std::cout << s << std::endl;
    }

	return 0;
}
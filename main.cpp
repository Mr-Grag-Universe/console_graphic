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
	
	return 0;
}
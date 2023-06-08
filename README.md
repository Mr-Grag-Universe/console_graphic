# 3D Console Renderer

This is my mini-project about Linux-console graphics.
It includes:

* Geometry modul
* Scene module
* main loop with rendering

## Geometry module

This module consists from basic abstracts and forms.
The basic unit here is a **Point** class. It can be treated as a point or as a free vector. 
Quite all other forms and structures are based on points and have **shared_poiters\<Point\>** in themselfs with it's alias: **poit_ptr**.

Main classes:

* Point
* Section
* Triangle
* Polihedron
* ClosedPolihedron

## Scene modele ##

As well as this is mini-project this modul is nos insulated. It consists from:

* Scene
* Camera
* Light and Object interfaces
* Light and Object implimentations

Here is main logic of my program.
There is main class Scene, that contain arrays of objects, cameras and light sources (LS).
All you can do with it is "take a look" from some camera and get matrix with information about intencety of light from LS, which richs each pixel.

Logic now:

1. get pixels grid from camera with some info about it [camera] like:

    * Resolution
    * Angle of view
    * Size
    * Position of it's center

2. for each pixel we calculate it's view direction
3. then we go throught ALL objets on the scene and find face of each one, that is the nearest for object
4. we find the nearest face from our list of faces selected faces
5. we calculate light intensity in the point of (pixel, direction)-line crossing this face using formula of scalar multiplication of vector to LS and normal to the face:

        I = -(V1, V2) * power
        Bright = max(I) / (1 + Dist^0.7)

6. function returns double-digits matrix of intensity

Later may be I'll add some color info to such matrix.

You can also add new variations of Objects and Light sources and make light behavior more realistic.

## Rendering ##

The next render process given matrix of intancity to char matrix of fixed diaposone.

This happening in the main loop.

Now btw I set my algorithm to move camera around the (0, 0, z) point, so each form, I put into the origin will cicle around itself.

## Intalling ##

This programm use Linux-core functions and works only in the terminal, so I guess it would work only in Unix-like OS.

Just clone this repository, build it with CMake and check out, how it works.
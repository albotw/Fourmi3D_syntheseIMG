#pragma once
#define _USE_MATH_DEFINES
#include <GL/freeglut.h>
#include <cmath>
#include <iostream>

typedef struct Point
{
    double x;
    double y;
    double z;
};

typedef struct Face
{
    int i;
    int j;
    int k;
    int l;
};

Point* sphere(int n, int m);

Face* sphere_faces(Point* sphere, int n, int m);

void render_sphere(Point* sphere, Face* face_sphere, int n, int m);
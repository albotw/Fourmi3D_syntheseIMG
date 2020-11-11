#pragma once
#define _USE_MATH_DEFINES
#include <GL/freeglut.h>
#include <cmath>
#include <iostream>

#include "Sphere.h"

Point* cylindre(int n, double hauteur, double rayon);
Face* cylindre_faces(Point* pts_cyl, int n);
void render_cylindre(Face* face_cyl, Point* pts_cyl, int n);
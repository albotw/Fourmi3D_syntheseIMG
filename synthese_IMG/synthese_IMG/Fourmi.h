#pragma once
#define _USE_MATH_DEFINES
#include <GL/freeglut.h>
#include <cmath>
#include <iostream>

#include "Sphere.h"

static double animValue_tete = 0.0;
static bool incrTete = true;
static double animValue_queue = 0.0;
static bool incrQueue = false;
static double animValue_antenne = 0.0;
static bool incrAntenne = true;
static double animValue_mandibule = 0.0;
static bool incrMandibule = false;
static double animValue_patte = 0.0;
static bool incrPatte = true;

static int n_oeil = 20;
static int m_oeil = 20;

static Point* pts_oeil1;
static Point* pts_oeil2;

static Face* faces_oeil1;
static Face* faces_oeil2;

void patte();
void antenne();
void abdomen();
void queue();
void mandibule();
void tete();
void fourmi();

void marron();
#pragma once

typedef unsigned int uint;
#include <vector>

#include <cassert>
#include <stdio.h>
#include <math.h>

#include <SDL.h>

#ifndef M_PI
#define M_PI 3.141592653
#endif

using namespace std;

double sq(double d1);
double distSq(double dx1, double dy1, double dx2, double dy2);
void distanceFromLine(double cx, double cy, double ax, double ay ,
                      double bx, double by, double &distanceSegment,
                      double &distanceLine);
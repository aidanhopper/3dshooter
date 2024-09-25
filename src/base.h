/**
 * @file
 * @brief Provides functions for basic interactions with SDL2.
 */

#pragma once

#include "hsl.h"
#include "matrix.h"
#include "mesh.h"
#include "v3.h"
#include "v4.h"
#include <SDL2/SDL.h>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
// #define DEBUG

void cleanup();
int init();
void pixel(int x, int y, int color);
void clear(int color);
void render();
void pline(int x0, int y0, int x1, int y1, int color);
int pixelList(int *list, int x0, int y0, int x1, int y1);
void ptriangle(int x0, int y0, int x1, int y1, int x2, int y2, int color);
void triangle(double x0, double y0, double x1, double y1, double x2, double y2,
              int color);
Matrix createProjectionMatrix();
Matrix createYRotMatrix(double theta);
Matrix createTranslationMatrix(v3 v);
Matrix createViewMatrix(v3 eye, v3 target, v3 up);

// values for the projection matrix
const double PI = 3.14159;
const double aspectRatio = (double)WINDOW_WIDTH / WINDOW_HEIGHT;
const double fov = 90; // in degrees
const double near = 1;
const double far = 100;

// target FPS
const int FPS = 144;

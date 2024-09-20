/**
 * @file
 * @brief Provides functions for basic interactions with SDL2.
 */

#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <stdexcept>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
//#define DEBUG

void cleanup();
int init();
void pixel(int x, int y, int color);
void clear(int color);
void render();
void pline(int x0, int y0, int x1, int y1, int color);
int pixelList(int *list, int x0, int y0, int x1, int y1);
void ptriangle(int x0, int y0, int x1, int y1, int x2, int y2, int color);
void triangle(double x0, double y0, double x1, double y1, double x2, double y2, int color);

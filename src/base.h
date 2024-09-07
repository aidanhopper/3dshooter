#pragma once

#include <SDL2/SDL.h>
#include <iostream>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600


void cleanup();
int init();
void pixel(int x, int y, int color);
void clear(int color);
void render();
void pline(int x0, int y0, int x1, int y1, int color);
void ptriangle(int x0, int y0, int x1, int y1, int x2, int y2, int color);

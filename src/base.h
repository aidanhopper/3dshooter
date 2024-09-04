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

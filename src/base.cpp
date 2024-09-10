#include "base.h"

SDL_Window *window = NULL; 
SDL_Surface *surface = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture = NULL;

void cleanup() {
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_FreeSurface(surface);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

int init() {

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    return 1;

  window = SDL_CreateWindow("Framebuffer Example", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
                            WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL)
    return 1;

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL)
    return 1;

  surface =
      SDL_CreateRGBSurface(0, WINDOW_WIDTH, WINDOW_HEIGHT, 32, 0, 0, 0, 0);
  if (surface == NULL)
    return 1;

  return 0;
}

void pixel(int x, int y, int color) {
  if (x >= WINDOW_WIDTH || y >= WINDOW_HEIGHT || x < 0 || y < 0)
    return;
  int *pixels = (int *)surface->pixels;
  pixels[y * surface->w + x] = color;
}

void clear(int color) { 
  SDL_FillRect(surface, NULL, color);
}

void render() {
  texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);
  SDL_DestroyTexture(texture);
}

// primitive line drawing algorithm
void pline(int x0, int y0, int x1, int y1, int color) {

  double dx = std::abs(x1 - x0);
  double sx = x0 < x1 ? 1 : -1;
  double dy = -std::abs(y1 - y0);
  double sy = y0 < y1 ? 1 : -1;
  double error = dx + dy;
  
  while (true) {
    pixel(x0, y0, color);
    if (x0 == x1 && y0 == y1)
      break;
    double e2 = 2 * error;
    if (e2 >= dy) {
      error = error + dy;
      x0 = x0 + sx;
    }
    if (e2 <= dx) {
      error = error + dx;
      y0 = y0 + sy;
    }
  }

}


int pixelList(int *list, int x0, int y0, int x1, int y1) {

  int dx = abs(x1 - x0);
  int sx = x0 < x1 ? 1 : -1;
  int dy = -abs(y1 - y0);
  int sy = y0 < y1 ? 1 : -1;
  int error = dx + dy;

  while (1) {
    if (y0 < WINDOW_HEIGHT && y0 >= 0)
      list[y0] = x0;
    if (x0 == x1 && y0 == y1)
      break;
    int e2 = 2 * error;
    if (e2 >= dy) {
      if (x0 == x1)
        break;
      error = error + dy;
      x0 = x0 + sx;
    }
    if (e2 <= dx) {
      if (y0 == y1)
        break;
      error = error + dx;
      y0 = y0 + sy;
    }
  }

  return 0;
}

// primitive triangle drawing algorithm
void ptriangle(int x0, int y0, int x1, int y1, int x2, int y2, int color) {
  pline(x0, y0, x1, y1, color);
  pline(x1, y1, x2, y2, color);
  pline(x0, y0, x2, y2, color);

#ifndef DEBUG

  if (y1 > y0) {
    ptriangle(x1, y1, x0, y0, x2, y2, color);
    return;
  }

  int linelist[WINDOW_HEIGHT];
  for (int i = 0; i < WINDOW_HEIGHT; i++)
    linelist[i] = -1;

  int linelist2[WINDOW_HEIGHT];
  for (int i = 0; i < WINDOW_HEIGHT; i++)
    linelist2[i] = -1;

  // need to draw 0 to 1 line and 0 to 2 line
  // and use linelist to check if im out of bounds

  int x0t = x0;
  int y0t = y0;
  int x1t = x1;
  int y1t = y1;
  int x2t = x2;
  int y2t = y2;

  pixelList(linelist, x1, y1, x2, y2);
  pixelList(linelist2, x0, y0, x2, y2);

  int dx = abs(x1 - x0);
  int sx = x0 < x1 ? 1 : -1;
  int dy = -abs(y1 - y0);
  int sy = y0 < y1 ? 1 : -1;
  int error = dx + dy;

  // draws from x0 to x2 line
  while (1) {
    if (linelist[y0] != -1)
      pline(x0, y0, linelist[y0], y0, color);
    if (linelist2[y0] != -1)
      pline(x0, y0, linelist2[y0], y0, color);
    if (x0 == x1 && y0 == y1)
      break;
    int e2 = 2 * error;
    if (e2 >= dy) {
      if (x0 == x1)
        break;
      error = error + dy;
      x0 = x0 + sx;
    }
    if (e2 <= dx) {
      if (y0 == y1)
        break;
      error = error + dx;
      y0 = y0 + sy;
    }
  }

  x0 = x0t;
  y0 = y0t;
  x1 = x2t;
  y1 = y2t;

  dx = abs(x1 - x0);
  sx = x0 < x1 ? 1 : -1;
  dy = -abs(y1 - y0);
  sy = y0 < y1 ? 1 : -1;
  error = dx + dy;

  // draws from x0 to x2 line
  while (1) {
    if (linelist[y0] != -1)
      pline(x0, y0, linelist[y0], y0, color);
    if (linelist2[y0] != -1)
      pline(x0, y0, linelist2[y0], y0, color);
    if (x0 == x1 && y0 == y1)
      break;
    int e2 = 2 * error;
    if (e2 >= dy) {
      if (x0 == x1)
        break;
      error = error + dy;
      x0 = x0 + sx;
    }
    if (e2 <= dx) {
      if (y0 == y1)
        break;
      error = error + dx;
      y0 = y0 + sy;
    }
  }

  x0 = x0t;
  x1 = x1t;
  x2 = x2t;
  y0 = y0t;
  y1 = y1t;
  y2 = y2t;
#endif
}

void triangle(double x0, double y0, double x1, double y1, double x2, double y2, int color) {
  int x0Screen = (int) (x0 * ((double) WINDOW_WIDTH/2) + ((double) WINDOW_WIDTH/2));
  int x1Screen = (int) (x1 * ((double) WINDOW_WIDTH/2) + ((double) WINDOW_WIDTH/2));
  int x2Screen = (int) (x2 * ((double) WINDOW_WIDTH/2) + ((double) WINDOW_WIDTH/2));
  int y0Screen = (int) (-y0 * ((double) WINDOW_HEIGHT/2) + ((double) WINDOW_HEIGHT/2));
  int y1Screen = (int) (-y1 * ((double) WINDOW_HEIGHT/2) + ((double) WINDOW_HEIGHT/2));
  int y2Screen = (int) (-y2 * ((double) WINDOW_HEIGHT/2) + ((double) WINDOW_HEIGHT/2));
  ptriangle(x0Screen, y0Screen, x1Screen, y1Screen, x2Screen, y2Screen, color);
}

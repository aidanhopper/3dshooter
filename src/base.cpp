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

// primitive triangle drawing algorithm
void ptriangle(int x0, int y0, int x1, int y1, int x2, int y2, int color, bool fill = true) {
  pline(x0, y0, x1, y1, color);
  pline(x1, y1, x2, y2, color);
  pline(x0, y0, x2, y2, color);

  //if ()

}

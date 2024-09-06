#include "base.h"

int main(int argc, char *argv[]) {
  if (init() != 0)
    return 1;

  SDL_Event event;
  while (true) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        return 0;
      }
    }

    clear(0x0);
    for (int i = 0; i < WINDOW_WIDTH; i++)
      pixel(i, i % WINDOW_HEIGHT, 0xF00FF);
    render();
  }

  cleanup();
}


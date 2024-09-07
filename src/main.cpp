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

    ptriangle(50, 50, 100, 100, 450, 10, 0xFFFFFF);

    render();
  }

  cleanup();
}


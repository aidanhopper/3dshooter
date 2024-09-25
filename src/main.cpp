/**
 * @file
 * @brief Entry point of the program.
 */

#include "base.h"

int main(int argc, char *argv[])
{
  // exit if init fails
  if (init() != 0)
  {
    return 1;
  }

  double theta = 0.0;

  Mesh mesh = Mesh("./objects/teapot.obj", HSL(0, 0, 1));

  // for hitting target FPS
  Uint32 frameStart;
  int frameTime;

  SDL_Event event;

  // game loop
  while (true)
  {
    frameStart = SDL_GetTicks();

    // event loop
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        return 0;
      }
    }

    v3 pos = v3(0, -2, -20);
    Matrix project = createProjectionMatrix();
    Matrix rot = createYRotMatrix(theta);
    Matrix translation = createTranslationMatrix(pos);
    Matrix transformation = project * translation * rot;

    clear(0x222222);

    // draw here

    mesh.draw(pos, v3(0, theta, 0));

    // end drawing

    render();

    // increment the angle
    theta += 0.01;

    // FPS calculations
    frameTime = SDL_GetTicks() - frameStart;
    if ((1000 / FPS) > frameTime)
    {
      SDL_Delay((1000 / FPS) - frameTime);
    }
  }

  cleanup();
}

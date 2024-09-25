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

  Mesh mesh = Mesh("./objects/mountains.obj", HSL(0, 0, 1));

  // for hitting target FPS
  Uint32 frameStart;
  int frameTime;

  SDL_Event event;

  v3 eye = v3(0, 0, 0);

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

      if (event.type == SDL_KEYDOWN)
      {
        switch (event.key.keysym.sym)
        {
        case SDLK_w:
          eye.z -= 0.1;
          break;
        case SDLK_a:
          eye.x -= 0.1;
          break;
        case SDLK_s:
          eye.z += 0.1;
          break;
        case SDLK_d:
          eye.x += 0.1;
          break;
        case SDLK_UP:
          eye.y += 0.1;
          break;
        case SDLK_DOWN:
          eye.y -= 0.1;
          break;
        }
      }
    }

    v3 pos = v3(0, -10, -20);
    Matrix project = createProjectionMatrix();
    Matrix rot = createYRotMatrix(theta);
    Matrix translation = createTranslationMatrix(pos);
    Matrix transformation = project * translation * rot;
    std::cout << eye << std::endl;

    clear(0x222222);

    // draw here

    mesh.draw(pos, v3(0, theta, 0), eye);

    // end drawing

    render();

    // increment the angle
    theta += 0.001;

    // FPS calculations
    frameTime = SDL_GetTicks() - frameStart;
    if ((1000 / FPS) > frameTime)
    {
      SDL_Delay((1000 / FPS) - frameTime);
    }
  }

  cleanup();
}

#include "base.h"
#include "triangle.h"
#include "matrix.h"
#include "v3.h"
#include "v4.h"

const double aspectRatio = WINDOW_WIDTH/WINDOW_HEIGHT;
const double fov = 90;
const double near = 1;
const double far = 100;

Matrix createProjectionMatrix() {
  return Matrix(
    1/(aspectRatio*std::tan(fov/2)), 0, 0, 0,
    0, tan(fov/2), 0, 0,
    0, 0, -(far+near)/(far-near), -2*far*near/(far-near),
    0, 0, -1, 0
  );
}

int main(int argc, char *argv[]) {
  if (init() != 0)
    return 1;

  Matrix projectionMatrix = createProjectionMatrix();  

  v3 p0 = v3(-1, 0, -5);
  v3 p1 = v3(-4, 1, -5);
  v3 p2 = v3(0, 0, -5);

  v2 p0projected = (projectionMatrix * p0.tov4()).perdiv();
  v2 p1projected = (projectionMatrix * p1.tov4()).perdiv();
  v2 p2projected = (projectionMatrix * p2.tov4()).perdiv();

  std::cout << projectionMatrix << std::endl;
  std::cout << projectionMatrix * p0.tov4() << std::endl;
  std::cout << projectionMatrix * p1.tov4() << std::endl;

  SDL_Event event;
  while (true) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        return 0;
      }
    }

    clear(0x222222);

    Triangle::draw(p0projected, p1projected, p2projected, 0xFFFFFF);

    render();
  }

  cleanup();
}


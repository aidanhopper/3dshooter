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

void trihelper(v3 p0, v3 p1, v3 p2, Matrix transformation) {
  Triangle::draw(
    (transformation * p0.tov4()).perdiv(), 
    (transformation * p1.tov4()).perdiv(),
    (transformation * p2.tov4()).perdiv(),
    0xFFFFFF
  );
}

void drawCube() {

  v3 p00 = v3(0, 0, -5);
  v3 p10 = v3(1, 0, -5);
  v3 p20 = v3(1, 1, -5);
  v3 p01 = v3(0, 0, -5);
  v3 p11 = v3(0, 1, -5);
  v3 p21 = v3(1, 1, -5);
  v3 p02 = v3(0, 0, -5);
  v3 p12 = v3(0, 1, -5);
  v3 p22 = v3(0, 1, -6);
  v3 p03 = v3(0, 0, -5);
  v3 p13 = v3(0, 0, -6);
  v3 p23 = v3(0, 1, -6);

  Matrix projectionMatrix = createProjectionMatrix();  

  trihelper(p00, p10, p20, projectionMatrix);
  trihelper(p01, p11, p21, projectionMatrix);
  trihelper(p02, p12, p22, projectionMatrix);
  trihelper(p03, p13, p23, projectionMatrix);

}

int main(int argc, char *argv[]) {
  if (init() != 0)
    return 1;

  Matrix projectionMatrix = createProjectionMatrix();  

  SDL_Event event;
  while (true) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        return 0;
      }
    }

    clear(0x222222);

    drawCube();

    render();
  }

  cleanup();
}


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

Matrix createXRotMatrix(double theta) {

}

Matrix createYRotMatrix(double theta) {

}

double createTransformationMatrix(v3 v) {

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

  v3 p04 = v3(0, 0, -6);
  v3 p14 = v3(1, 0, -6);
  v3 p24 = v3(1, 1, -6);

  v3 p05 = v3(0, 0, -6);
  v3 p15 = v3(0, 1, -6);
  v3 p25 = v3(1, 1, -6);

  Matrix projectionMatrix = createProjectionMatrix();  

  Triangle::draw(p00, p10, p20, 0xFFFFFF, projectionMatrix);
  Triangle::draw(p01, p11, p21, 0xFFFFFF, projectionMatrix);
  Triangle::draw(p02, p12, p22, 0xFFFFFF, projectionMatrix);
  Triangle::draw(p03, p13, p23, 0xFFFFFF, projectionMatrix);
  Triangle::draw(p04, p14, p24, 0xFFFFFF, projectionMatrix);
  Triangle::draw(p05, p15, p25, 0xFFFFFF, projectionMatrix);

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


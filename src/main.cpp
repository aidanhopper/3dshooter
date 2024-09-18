#include "base.h"
#include "triangle.h"
#include "matrix.h"
#include "v3.h"
#include "v4.h"

const double PI = 3.14159;

const double aspectRatio = (double) WINDOW_WIDTH/WINDOW_HEIGHT;
const double fov = 90; // in degrees
const double near = 1;
const double far = 100;

Matrix createProjectionMatrix() {
  float scale = 1 / std::tan(fov * 0.5 * PI/180);
  return Matrix(
    (1/aspectRatio)*scale, 0, 0, 0,
    0, scale, 0, 0,
    0, 0, -(far+near)/(far-near), -2*far*near/(far-near),
    0, 0, -1, 0
  );
}

// Matrix createXRotMatrix(double theta) {
// }

Matrix createYRotMatrix(double theta) {
  return Matrix(
    std::cos(theta), 0, std::sin(theta), 0,
    0, 1, 0, 0,
    -std::sin(theta), 0, std::cos(theta), 0,
    0, 0, 0, 1
  );
}

Matrix createTranslationMatrix(v3 v) {
  return Matrix(
    1, 0, 0, v.x,
    0, 1, 0, v.y,
    0, 0, 1, v.z,
    0, 0, 0, 1
  );
}

void drawFace(v3 p0, v3 p1, v3 p2, v3 p3, v3 pos, double theta) {
  Matrix project = createProjectionMatrix();  
  Matrix rot = createYRotMatrix(theta);
  Matrix translate = createTranslationMatrix(pos);

  v2 p0transformed = (project * translate * rot * p0.tov4()).perspectiveDivide().tov2();
  v2 p1transformed = (project * translate * rot * p1.tov4()).perspectiveDivide().tov2();
  v2 p2transformed = (project * translate * rot * p2.tov4()).perspectiveDivide().tov2();
  v2 p3transformed = (project * translate * rot * p3.tov4()).perspectiveDivide().tov2();

  Triangle::draw(
    p0transformed,
    p1transformed,
    p2transformed,
    0xFFFFFF
  );

  Triangle::draw(
    p1transformed,
    p2transformed,
    p3transformed,
    0xFFFFFF
  );
}

void drawCube(double theta) {

  v3 face10 = v3(1, 0, -0);
  v3 face11 = v3(0, 0, -1);
  v3 face12 = v3(0, 1, -1);
  v3 face13 = v3(0, 1, -0);

  v3 face20 = v3(0, 0, -0);
  v3 face21 = v3(1, 0, -0);
  v3 face22 = v3(1, 1, -0);
  v3 face23 = v3(0, 1, -0);

  v3 face30 = v3(1, 0, -0);
  v3 face31 = v3(1, 0, -1);
  v3 face32 = v3(1, 1, -1);
  v3 face33 = v3(1, 1, -0);

  v3 face40 = v3(0, 0, -1);
  v3 face41 = v3(1, 0, -1);
  v3 face42 = v3(1, 1, -1);
  v3 face43 = v3(0, 1, -1);

  v3 face50 = v3(0, 0, -0);
  v3 face51 = v3(1, 0, -0);
  v3 face52 = v3(1, 0, -1);
  v3 face53 = v3(0, 0, -1);

  v3 face60 = v3(0, 1, -0);
  v3 face61 = v3(1, 1, -0);
  v3 face62 = v3(1, 1, -1);
  v3 face63 = v3(0, 1, -1);

  v3 pos = v3(-0.5, -0.5, -3);

  drawFace(face10, face11, face12, face13, pos, theta);
  drawFace(face20, face21, face22, face23, pos, theta);
  drawFace(face30, face31, face32, face33, pos, theta);
  drawFace(face40, face41, face42, face43, pos, theta);
  drawFace(face50, face51, face52, face53, pos, theta);
  drawFace(face60, face61, face62, face63, pos, theta);
}



int main(int argc, char *argv[]) {
  if (init() != 0)
    return 1;

  double theta = 0.001;

  SDL_Event event;
  while (true) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        return 0;
      }
    }

    clear(0x222222);

    drawCube(theta);

    render();

    theta += 0.001;

  }

  cleanup();
}


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

// BUG
// The matrix * matrix multiplication
// is producing incorrect outputs
void drawPoint(v3 p0, v3 p1, v3 p2, v3 pos, double theta) {
  Matrix project = createProjectionMatrix();  
  Matrix rot = createYRotMatrix(theta);
  Matrix translate = createTranslationMatrix(v3(10, 10, -10));

  v4 p0transformed = translate * project * p0.tov4();
  v4 p1transformed = translate * project * p1.tov4();
  v4 p2transformed = translate * project * p2.tov4();

  std:: cout << project * v4(0.5, 0.5, 0.5, 1) << std::endl;

  //Triangle::draw(
  //  (translate * project * p0.tov4()).perdiv(),
  //  (translate * project * p1.tov4()).perdiv(),
  //  (translate * project * p2.tov4()).perdiv(),
  //  0xFFFFFF
  //);
}

void drawCube(double theta) {

  v3 p00 = v3(0, 0, -0); v3 p10 = v3(1, 0, -0);
  v3 p20 = v3(1, 1, 1);

  v3 p01 = v3(0, 0, -0);
  v3 p11 = v3(0, 1, -0);
  v3 p21 = v3(1, 1, -0);

  v3 p02 = v3(0, 0, -0);
  v3 p12 = v3(0, 1, -0);
  v3 p22 = v3(0, 1, -1);

  v3 p03 = v3(0, 0, -0);
  v3 p13 = v3(0, 0, -1);
  v3 p23 = v3(0, 1, -1);

  v3 p04 = v3(0, 0, -1);
  v3 p14 = v3(1, 0, -1);
  v3 p24 = v3(1, 1, -1);

  v3 p05 = v3(0, 0, -1);
  v3 p15 = v3(0, 1, -1);
  v3 p25 = v3(1, 1, -1);

  v3 pos = v3(10, 10, -90);

  drawPoint(p00, p10, p20, pos, theta);
  //drawPoint(p01, p11, p21, pos, theta);
  //drawPoint(p02, p12, p22, pos, theta);
  //drawPoint(p03, p13, p23, pos, theta);
  //drawPoint(p04, p14, p24, pos, theta);
  //drawPoint(p05, p15, p25, pos, theta);
}



int main(int argc, char *argv[]) {
  //if (init() != 0)
  //  return 1;

  double theta = 0;

  SDL_Event event;
  while (true) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        return 0;
      }
    }

    //clear(0x222222);

    drawCube(theta);

    //render();

    theta += 0.001;

  }

  //cleanup();
}


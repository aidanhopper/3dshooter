#include "base.h"
#include "triangle.h"
#include "matrix.h"
#include "v3.h"
#include "v4.h"
#include "hsl.h"

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

void drawCube(double theta) {

  v3 p0 = v3(0, 0, 0);
  v3 p1 = v3(1, 0, 0);
  v3 p2 = v3(0, 1, 0);

  v3 pos = v3(-0.5, -0.5, -3);

  Matrix project = createProjectionMatrix();
  Matrix rot = createYRotMatrix(theta);
  Matrix translation = createTranslationMatrix(pos);

  v4 p0cam = translation * rot * p0.tov4();
  v4 p1cam = translation * rot * p1.tov4();
  v4 p2cam = translation * rot * p2.tov4();

  v3 p0screen = (project * p0cam).perspectiveDivide();
  v3 p1screen = (project * p1cam).perspectiveDivide();
  v3 p2screen = (project * p2cam).perspectiveDivide();

  v3 normal = (p1screen - p0screen).cross(p2screen- p0screen);

  double luminence = -normal.dot(v3(0, 0, -1));

  if (luminence >= 0) {
    HSL color = HSL(1.0,1.0,1.0);
    std::cout << color << std::endl;
    Triangle::draw(
      p0screen.tov2(),
      p1screen.tov2(),
      p2screen.tov2(),
      color.toHex()
    );
  }

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


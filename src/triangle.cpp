#include "triangle.h"

namespace Triangle {
  void draw(int x0, int y0, int x1, int y1, int x2, int y2, int color) {
    ptriangle(x0, y0, x1, y1, x2, y2, color);
  }

  void draw(double x0, double y0, double x1, double y1, double x2, double y2, int color) {
    triangle(x0, y0, x1, y1, x2, y2, color);
  }

  void draw(v2 p0, v2 p1, v2 p2, int color) {
    triangle(p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, color);
  }

}

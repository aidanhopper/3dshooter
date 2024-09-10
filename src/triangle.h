#pragma once

#include "v2.h"

namespace Triangle {
  void draw(int x0, int y0, int x1, int y1, int x2, int y2, int color);
  void draw(double x0, double y0, double x1, double y1, double x2, double y2, int color);
  void draw(v2 p0, v2 p1, v2 p2, int color);
}

#pragma once

#include <iostream>
#include <cmath>

#include "v3.h"
#include "v2.h"

class v3;

class v4 {
public:
  double x;
  double y;
  double z;
  double w;
  v4();
  v4(double x, double y, double z, double w);
  v4 norm();
  v3 tov3();
  v3 perspectiveDivide();
  friend std::ostream& operator<< (std::ostream &out, const v4 &v);
};

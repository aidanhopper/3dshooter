#pragma once

#include <iostream>
#include <cmath>

class v2 {
public:
  double x;
  double y;
  v2(double x, double y);
  v2 norm();
  friend std::ostream& operator<< (std::ostream &out, const v2 &v);
};

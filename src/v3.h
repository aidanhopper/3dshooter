#pragma once

#include <iostream>
#include <cmath>

#include "v4.h"
#include "v2.h"

class v4;

class v3 {
public:
  double x;
  double y;
  double z;
  v3();
  v3(double x, double y, double z);
  v3 norm();
  v4 tov4();
  v2 perdiv(); // perspective divide
  friend std::ostream& operator<< (std::ostream &out, const v3 &v);
};

v3 cross(v3 v1, v3 v2);

double dot(v3 v1, v3 v2);

#pragma once

#include <iostream>
#include <cmath>

class HSL {
private:
  double hueToRGB(double p, double q, double t);
public:
  double hue;
  double saturation;
  double luminence;
  HSL(int color);
  HSL(double hue, double saturation, double luminence);
  int toHex();
  friend std::ostream& operator<< (std::ostream &out, const HSL &color);
};

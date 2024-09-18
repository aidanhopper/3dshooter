#pragma once

#include <iostream>

class HSL {
public:
  double hue;
  double saturation;
  double luminence;
  HSL(int color);
  HSL(double hue, double saturation, double luminence);
  int toHex();
  friend std::ostream& operator<< (std::ostream &out, const HSL &color);
};

#include "hsl.h"

HSL::HSL(int color) {
  // need to convert this to HSL form
  std::cout << color << std::endl;
}

HSL::HSL(double hue, double saturation, double luminence) {
  this->hue = hue;
  this->saturation = saturation;
  this->luminence = luminence;
}

int HSL::toHex() {
  return 0xFFFFFF;  // temporary return value
}

std::ostream& operator<< (std::ostream &out, const HSL &color) {
  out << "[ H: " << color.hue 
      <<  " S: " << color.saturation 
      <<  " L: " << color.luminence << " ]";
  return out;
}

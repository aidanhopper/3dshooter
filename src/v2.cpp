#include "v2.h"

v2::v2(double x, double y) {
  this->x = x;
  this->y = y;
}

v2 v2::norm() {
  double d = std::sqrt(
    this->x*this->x + this->y*this->y
  );
  return v2(this->x/d, this->y/d);
}

std::ostream& operator<< (std::ostream &out, const v2 &v) {
  out << "[ " << v.x << " " << v.y << " ]";
  return out;
}

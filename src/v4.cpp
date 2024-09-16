#include "v4.h"
#include "v3.h"
#include "base.h"

v4::v4(double x, double y, double z, double w) {
  this->x = x;
  this->y = y;
  this->z = z;
  this->w = w;
}

v3 v4::tov3() {
  return v3(this->x, this->y, this->z);
}

std::ostream& operator<< (std::ostream &out, const v4 &v) {
  out << "[ " << v.x << " " << v.y << " " << v.z << " " << v.w << " ]";
  return out;
}

v2 v4::perdiv() {
  v2 out = v2(this->x/this->w, this->y/this->w);
  //std::cout << *this << std::endl;
  return out;
}

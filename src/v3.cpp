#include "v3.h"

v3::v3() {
  this->x = 0;
  this->y = 0;
  this->z = 0;
}

v3::v3(double x, double y, double z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

v3 v3::norm() {
  double d = std::sqrt(
    this->x*this->x + this->y*this->y + this->z*this->z
  );
  return v3(this->x/d, this->y/d, this->z/d);
}

v4 v3::tov4() {
  return v4(this->x, this->y, this->z, 1);
}

std::ostream& operator<< (std::ostream &out, const v3 &v) {
  out << "[ " << v.x << " " << v.y << " " << v.z << " ]";
  return out;
}


v3 cross(v3 v1, v3 v2) {
  return v1;
}

double dot(v3 v1, v3 v2) {
  return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

v2 v3::perdiv() {
  return v2(this->x/this->z, this->y/this->z);
}

v3 operator* (const v3 &v, const double &s) {
  return v3(v.x * s, v.y * s, v.z * s);
}

v3 operator* (const double &s, const v3 &v) {
  return v3(v.x * s, v.y * s, v.z * s);
}

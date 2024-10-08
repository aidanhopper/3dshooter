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
  double d = std::sqrt( this->x*this->x + this->y*this->y + this->z*this->z);
  return v3(this->x/d, this->y/d, this->z/d);
}

v4 v3::tov4() {
  return v4(this->x, this->y, this->z, 1);
}

v2 v3::tov2() {
  return v2(this->x, this->y);
}

std::ostream& operator<< (std::ostream &out, const v3 &v) {
  out << "[ " << v.x << " " << v.y << " " << v.z << " ]";
  return out;
}

double v3::dot(v3 v) {
  return this->x*v.x + this->y*v.y + this->z*v.z;
}

v3 v3::cross(v3 v2) {
  v3 v1 = *this;
  return v3(
    v1.y*v2.z - v1.z*v2.y,
    v1.z*v2.x - v1.x*v2.z,
    v1.x*v2.y - v1.y*v2.x
  );
}

v3 operator* (const v3 &v, const double &s) {
  return v3(v.x * s, v.y * s, v.z * s);
}

v3 operator* (const double &s, const v3 &v) {
  return v3(v.x * s, v.y * s, v.z * s);
}

v3 operator- (const v3 &v1, const v3 &v2) {
  return v3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

v3 operator+ (const v3 &v1, const v3 &v2) {
  return v3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

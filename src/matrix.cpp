#include "base.h"
#include "matrix.h"

Matrix::Matrix(
  double a00, double a01, double a02, double a03, 
  double a10, double a11, double a12, double a13, 
  double a20, double a21, double a22, double a23, 
  double a30, double a31, double a32, double a33
) {
  this->s = 4;
  this->m[0][0] = a00; this->m[0][1] = a01; this->m[0][2] = a02; this->m[0][3] = a03;
  this->m[1][0] = a10; this->m[1][1] = a11; this->m[1][2] = a12; this->m[1][3] = a13;
  this->m[2][0] = a20; this->m[2][1] = a21; this->m[2][2] = a22; this->m[2][3] = a23;
  this->m[3][0] = a30; this->m[3][1] = a31; this->m[3][2] = a32; this->m[3][3] = a33;
}

Matrix::Matrix(
  double a00, double a01, double a02, 
  double a10, double a11, double a12, 
  double a20, double a21, double a22
) {
  this->s = 3;
  this->m[0][0] = a00; this->m[0][1] = a01; this->m[0][2] = a02;
  this->m[1][0] = a10; this->m[1][1] = a11; this->m[1][2] = a12;
  this->m[2][0] = a20; this->m[2][1] = a21; this->m[2][2] = a22;
}

Matrix::Matrix(
  double a00, double a01,
  double a10, double a11
) {
  this->s = 2;
  this->m[0][0] = a00; this->m[0][1] = a01;
  this->m[1][0] = a10; this->m[1][1] = a11;
}

Matrix::Matrix(int s, double m[4][4]) {
  this->s = s;
  for (int i = 0; i < this->s; i++)
    for (int j = 0; j < this->s; j++)
      this->m[i][j] = m[i][j];
}

int Matrix::size() {
  return this->s;
}

std::ostream& operator<< (std::ostream &out, const Matrix &m) {
  out << std::fixed;
  out << std::setprecision(5);
  out << "[";
  for (int i = 0; i < m.s; i++) {
    out << " ";
   if (i != 0)
      out << " ";
    for (int j = 0; j < m.s; j++) {
      out << m.m[i][j];
      if (j != m.s - 1)
        out << " ";
    }
    if (m.s - 1 != i)
      out << std::endl;
  }
  out << " ]";
  return out;
}

double* Matrix::operator[] (unsigned i) {
  return this->m[i];
}

Matrix operator* (const Matrix &m1, const Matrix &m2) {
  // make sure matrices are the same size
  if (m1.s != m2.s)
    throw std::invalid_argument("matrix dimensions should be the same");

  double newMatrix[4][4];

  for (int i = 0; i < m1.s; i++) {
    for (int j = 0; j < m1.s; j++) {
      newMatrix[i][j] = 0;
      for (int k = 0; k < m1.s; k++) {
        newMatrix[i][j] += m1.m[i][k] * m2.m[k][j];
      }
    }
  }

  return Matrix(m2.s, newMatrix);
}


v4 operator* (const Matrix &m, const v4 &v) {
  if (m.s != 4)
    throw std::invalid_argument("this function only supports 4x4 matrices");

  double oldVector[4] = { v.x, v.y, v.z, v.w };
  double newVector[4] = { 0.0, 0.0, 0.0, 0.0 };

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      newVector[i] += oldVector[j] * m.m[i][j];

  return v4(newVector[0], newVector[1], newVector[2], newVector[3]);
}

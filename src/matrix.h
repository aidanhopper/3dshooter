#pragma once

#include <iostream>
#include <iomanip>
#include "v3.h"
#include "v4.h"

class Matrix {
private:
  int s;
  double m[4][4];
public:
  Matrix(
    double a00, double a01, double a02, double a03, 
    double a10, double a11, double a12, double a13, 
    double a20, double a21, double a22, double a23, 
    double a30, double a31, double a32, double a33
  );
  Matrix(
    double a00, double a01, double a02, 
    double a10, double a11, double a12, 
    double a20, double a21, double a22
  );
  Matrix(
    double a00, double a01,
    double a10, double a11
  );
  Matrix(int s, double m[4][4]);
  int size();
  Matrix invert();
  double* operator[] (unsigned i);
  friend std::ostream& operator<< (std::ostream &out, const Matrix &m);
  friend Matrix operator* (const Matrix &m1, const Matrix &m2);

  // TODO implement these operator overloads
  friend v4 operator* (const Matrix &m, const v4 &v);
  //friend Matrix operator* (const v3 &v, const Matrix &m);
};

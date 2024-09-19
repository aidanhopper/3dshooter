#pragma once

#include "v3.h"
#include "hsl.h"
#include "triangle.h"
#include "matrix.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <array>
#include <algorithm>

class Mesh {
private:
  std::vector<v3> vertices;
  std::vector<std::array<int, 3>> faces;
  HSL color;
  std::vector<std::string> split(std::string str, std::string del);
public:
  Mesh(const char *path, HSL color); 
  void draw(Matrix transform);
};

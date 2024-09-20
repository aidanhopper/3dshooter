/**
 * @file mesh.h
 * @brief Header file that defines the Mesh class
 */

#pragma once

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "hsl.h"
#include "matrix.h"
#include "triangle.h"
#include "v3.h"

/**
 * @class Mesh
 * @brief Class that represents object meshes that can be drawn on screen.
 *
 */
class Mesh {
 private:
  /**
   * @brief Vector of v3's that represents a point in model space.
   */
  std::vector<v3> vertices;
  /**
   * @brief Vector of arrays which represent triangles as indexes in the
   * vertices vector.
   */
  std::vector<std::array<int, 3>> faces;

  HSL color;
  std::vector<std::string> split(std::string str, std::string del);

 public:
  Mesh(const char *path, HSL color);
  void draw(Matrix transform);
};

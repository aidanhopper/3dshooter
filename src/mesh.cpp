/**
 * @file
 * @brief Contains the definitions of methods in the Mesh class.
 */

#include "mesh.h"

/**
 * @brief Constructor class that takes the file path of the .obj file
 * and constructs the vertices and faces vectors
 *
 * @param path of the file
 * @param color of the object
 */
Mesh::Mesh(const char *path, HSL color)
{
  this->color = color;
  std::ifstream f(path);

  if (f.is_open())
  {
    std::string contents;

    while (getline(f, contents))
    {
      // handles vertices
      if (contents[0] == 'v')
      {
        std::vector<std::string> res = this->split(contents, " ");
        double x = std::stod(res[0]);
        double y = std::stod(res[1]);
        double z = std::stod(res[2]);
        v3 vertex(x, y, z);
        this->vertices.push_back(vertex);
      }

      // handles faces
      if (contents[0] == 'f')
      {
        std::vector<std::string> res = this->split(contents, " ");
        int p0 = std::stoi(res[0]) - 1;
        int p1 = std::stoi(res[1]) - 1;
        int p2 = std::stoi(res[2]) - 1;
        std::array<int, 3> arr{p0, p1, p2};
        this->faces.push_back(arr);
      }
    }
  }
}

std::vector<std::string> Mesh::split(std::string str, std::string del)
{
  int first;
  int last = 2;
  std::vector<std::string> result;
  while ((first = str.find_first_not_of(" ", last)) != std::string::npos)
  {
    last = str.find(" ", first);
    result.push_back(str.substr(first, last - first));
  }
  return result;
}

/**
 * @brief Draws the mesh.
 *
 * @param transform The transformation that is applied to the points in the
 * mesh.
 *
 * TODO implement Cohen-Sutherland line clipping
 */
void Mesh::draw(Matrix transform)
{
  std::vector<std::array<v3, 3>> draworder;

  // populates draworder with triangles that need to be drawn
  for (auto face : this->faces)
  {
    // grab points
    v3 p0 = this->vertices[face[0]];
    v3 p1 = this->vertices[face[1]];
    v3 p2 = this->vertices[face[2]];

    // transform points
    v4 p0t = (transform * p0.tov4());
    v4 p1t = (transform * p1.tov4());
    v4 p2t = (transform * p2.tov4());

    v3 normal = (p1t.perspectiveDivide() - p0t.perspectiveDivide())
                    .cross(p2t.perspectiveDivide() - p0t.perspectiveDivide())
                    .norm();

    double dir = normal.dot(v3(0, 0, -1));

    // push points to vector that are in view for sorting later
    if (dir < 0 && std::abs(p0t.x) < p0t.w && std::abs(p0t.y) < p0t.w &&
        std::abs(p0t.z) < p0t.w && std::abs(p1t.x) < p1t.w &&
        std::abs(p1t.y) < p1t.w && std::abs(p1t.z) < p1t.w &&
        std::abs(p2t.x) < p2t.w && std::abs(p2t.y) < p2t.w &&
        std::abs(p2t.z) < p2t.w)
    {
      draworder.push_back({p0t.perspectiveDivide(), p1t.perspectiveDivide(),
                           p2t.perspectiveDivide()});
    }
  }

  // sort points by depth from back to front (painters algorithm)
  std::sort(draworder.begin(), draworder.end(),
            [](std::array<v3, 3> points1, std::array<v3, 3> points2) {
              double average1 =
                  (points1[0].z + points1[1].z + points1[2].z) / 3;
              double average2 =
                  (points2[0].z + points2[1].z + points2[2].z) / 3;
              return (average1 > average2);
            });

  // draw the triangles in the draw order
  for (auto point : draworder)
  {
    HSL col = this->color;
    v3 normal = (point[1] - point[0]).cross(point[2] - point[0]).norm();
    double dir = normal.dot(v3(0, 0, -1));
    col.luminence = -dir * 0.95;
    Triangle::draw(point[0].tov2(), point[1].tov2(), point[2].tov2(),
                   col.toHex());
  }
}

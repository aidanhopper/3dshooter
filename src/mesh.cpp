#include "mesh.h"

Mesh::Mesh(const char *path, HSL color) {
  this->color = color;
  std::ifstream f (path);

  if (f.is_open()) {

    std::string contents;

    while (getline(f, contents)) {
      
      // handles vertices
      if (contents[0] == 'v') {
        std::vector<std::string> res = this->split(contents, " ");
        double x = std::stod(res[0]);
        double y = std::stod(res[1]);
        double z = std::stod(res[2]);
        v3 vertex (x, y, z);
        this->vertices.push_back(vertex);
      }

      // handles faces
      if (contents[0] == 'f') {
        std::vector<std::string> res = this->split(contents, " ");
        int p0 = std::stoi(res[0]) - 1;
        int p1 = std::stoi(res[1]) - 1;
        int p2 = std::stoi(res[2]) - 1;
        std::array<int, 3> arr { p0, p1, p2 };
        this->faces.push_back(arr);
      }

    }

  }

}

std::vector<std::string> Mesh::split(std::string str, std::string del) {
  int first;
  int last = 2;
  std::vector<std::string> result;
  while ((first = str.find_first_not_of(" ", last)) 
    != std::string::npos) {
    last = str.find(" ", first);
    result.push_back(str.substr(first, last - first));
  }
  return result;
}

void Mesh::draw(Matrix transform) {

  std::vector<std::array<v3, 3>> draworder;

  for (auto face : this->faces) {
    v3 p0 = this->vertices[face[0]];
    v3 p1 = this->vertices[face[1]];
    v3 p2 = this->vertices[face[2]];

    v3 p0screen = (transform * p0.tov4()).perspectiveDivide();
    v3 p1screen = (transform * p1.tov4()).perspectiveDivide();
    v3 p2screen = (transform * p2.tov4()).perspectiveDivide();

    v3 normal = (p1screen - p0screen).cross(p2screen - p0screen);
    double dir = normal.dot(v3(0, 0, -1));
    
    if (dir < 0) {
      draworder.push_back({p0, p1, p2});
    }

  }

  std::sort(
    draworder.begin(),
    draworder.end(), 
    [](std::array<v3,3> points1, std::array<v3, 3> points2) {
      double average1 = (points1[0].z + points1[1].z + points1[2].z)/3;
      double average2 = (points2[0].z + points2[1].z + points2[2].z)/3;
      return (average1 < average2);
  });

  for (auto point : draworder) {

    HSL col = this->color;
    v3 normal = (point[1] - point[0]).cross(point[2] - point[0]);
    double dir = normal.dot(v3(0, 0, -1));
    col.luminence = std::min(1., col.luminence * dir * 1.5);

    std::cout << dir << std::endl;

    Triangle::draw(
      (transform * point[0].tov4()).perspectiveDivide().tov2(),
      (transform * point[1].tov4()).perspectiveDivide().tov2(),
      (transform * point[2].tov4()).perspectiveDivide().tov2(),
      col.toHex()
    );

  }
}

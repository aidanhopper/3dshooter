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
        std::cout << vertex << std::endl;
        this->vertices.push_back(vertex);
      }

      // handles faces
      if (contents[0] == 'f') {
        std::vector<std::string> res = this->split(contents, " ");
        int p0 = std::stoi(res[0]);
        int p1 = std::stoi(res[1]);
        int p2 = std::stoi(res[2]);
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
  for (auto face : this->faces) {
    v3 p0 = this->vertices[face[0]];
    v3 p1 = this->vertices[face[1]];
    v3 p2 = this->vertices[face[2]];

    v3 p0screen = (transform * p0.tov4()).perspectiveDivide();
    v3 p1screen = (transform * p1.tov4()).perspectiveDivide();
    v3 p2screen = (transform * p2.tov4()).perspectiveDivide();

    v3 normal = (p1screen - p0screen).cross(p2screen - p0screen);

    double dir = normal.dot(v3(0, 0, -1));

    if (dir >= 0) {
      double luminence = std::max(0., dir);
      HSL col = this->color;
      col.luminence = luminence;
      Triangle::draw(
        p0screen.tov2(),
        p1screen.tov2(),
        p2screen.tov2(),
        col.toHex()
      );
    }


  }
}

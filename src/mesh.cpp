/**
 * @file
 * @brief Contains the definitions of methods in the Mesh class.
 *
 * Eventually this class will need to be restructured to account for
 * objects such as camera (has not been created yet) and to make a more
 * robust system for apply transformations.
 *
 * A different transformation system would go like this.
 *
 * 1. Apply matrix to transform the model.
 * ... do stuff
 * 2. Apply matrix to transform from model space to world space.
 * ... do stuff to the points
 * 3. Apply matrix to transform from world space to view space.
 * ... do stuff to the points
 * 4. Apply matrix to transform from view space to screen space.
 * ... do stuff
 * draw
 *
 * This way the function signature would look like this.
 * draw(Matrix modelT, Matrix worldT, Matrix viewT, Matrix screenT, ...)
 *
 * This will give the ability to control the transfomrations that occur at
 * different stages of the projection pipeline.
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
 * @brief Takes a vector points that are facing the camera and
 * removes them when they are outside the view frustum.
 *
 * @param v The vector containing the points in view space.
 */
void Mesh::clip(std::vector<std::array<v3, 3>> &v)
{
}

/**
 * @brief Populates the draw vector with triangles that should be drawn in draw
 * order.
 *
 * Vertices should be projected and divided by perspective before being added
 * to the draw vector.
 *
 * @param v The vector to populate.
 */
void Mesh::populateDrawVector(std::vector<std::array<v3, 3>> &v, v3 pos,
                              v3 rot)
{
  // create matrices
  Matrix project = createProjectionMatrix();
  Matrix translate = createTranslationMatrix(pos);
  Matrix yrot = createYRotMatrix(rot.y);
  Matrix view = createViewMatrix(v3(0, 0, 0), v3(0, 0, -1), v3(0, 1, 0));

  // populates draworder with triangles that need to be drawn
  for (auto face : this->faces)
  {
    // grab points
    v3 p0model = this->vertices[face[0]];
    v3 p1model = this->vertices[face[1]];
    v3 p2model = this->vertices[face[2]];

    // project points into view space for clipping
    v3 p0view = (view * translate * yrot * p0model.tov4()).tov3();
    v3 p1view = (view * translate * yrot * p1model.tov4()).tov3();
    v3 p2view = (view * translate * yrot * p2model.tov4()).tov3();

    // project points to check if the triangle is facing the camera
    v3 a = (project * p0view.tov4()).perspectiveDivide();
    v3 b = (project * p1view.tov4()).perspectiveDivide();
    v3 c = (project * p2view.tov4()).perspectiveDivide();

    v3 ab = b - a;
    v3 ac = c - a;

    // check if triangle is facing the camera
    bool triIsFacingCamera = ab.x * ac.y - ac.x * ab.y < 0 ? false : true;

    // add points to the draworder when they are facing the camera and do crude
    // (not sorted yet)
    if (triIsFacingCamera)
    {
      v.push_back({a, b, c});
    }
  }

  // sort points by depth from back to front (painters algorithm)
  std::sort(v.begin(), v.end(),
            [](std::array<v3, 3> points1, std::array<v3, 3> points2) {
              double average1 =
                  (points1[0].z + points1[1].z + points1[2].z) / 3;
              double average2 =
                  (points2[0].z + points2[1].z + points2[2].z) / 3;
              return (average1 > average2);
            });
}

/**
 * @brief Draws the mesh.
 *
 * @param transform The transformation that is applied to the points in the
 * mesh.
 *
 * TODO implement the view matrix
 * TODO implement Cohen-Sutherland line clipping
 */
void Mesh::draw(v3 pos, v3 rot)
{

  std::vector<std::array<v3, 3>> draworder;

  this->populateDrawVector(draworder, pos, rot);

  // draw the triangles in the draw order
  for (auto point : draworder)
  {
    // get dir to determine the strength of the light source
    v3 normal = (point[1] - point[0]).cross(point[2] - point[0]).norm();
    double dir = normal.dot(v3(0, 0, -1));

    // project points to screen and convert to v2
    v2 p0p = point[0].tov2();
    v2 p1p = point[1].tov2();
    v2 p2p = point[2].tov2();

    // draw the triangle on screen
    Triangle::draw(p0p, p1p, p2p,
                   this->color.modifyLuminence(-dir * 0.95).toHex());
  }
}

#ifndef MESH_HPP
#define MESH_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>

#include "Shader.hpp"

struct Vertex_st {
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 texcoords;
};

struct Texture_st {
  unsigned int id;
  std::string type;
  std::string path;
};

class Mesh
{
private:
  std::vector<Vertex_st> _vertices;
  std::vector<unsigned int> _indices;
  std::vector<Texture_st> _textures;
  unsigned int VAO, VBO, EBO;
public:
  Mesh(std::vector<Vertex_st> vertices, std::vector<unsigned int> indices, std::vector<Texture_st> textures);
  ~Mesh();
  void draw(Shader shader);
};

#endif

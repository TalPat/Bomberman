#include "Mesh.hpp"

Mesh::Mesh(std::vector<Vertex_st> vertices, std::vector<unsigned int> indices, std::vector<Texture_st> textures):
  _vertices(vertices),
  _indices(indices),
  _textures(textures)
{
  /**/for(int i = 0; i < _textures.size();i++) std::cout << _textures[i].id << "  " <<  _textures[i].path << "  "  <<  _textures[i].type << std::endl;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER ,VBO);

  //for (int i =0; i < vertices.size();i++) std::cout << vertices[i].position.x << "  " << vertices[i].position.y << "  "  << vertices[i].position.z << std::endl;

  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex_st), &vertices[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_st), (void*)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_st), (void*)offsetof(Vertex_st, normal));
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_st), (void*)offsetof(Vertex_st, texcoords));

  glBindVertexArray(0);
}

Mesh::~Mesh() {

}

void Mesh::draw(Shader shader) {
  unsigned int diffuseNr = 1;
  unsigned int specularNr = 1;

  for (unsigned int i = 0; i < _textures.size(); i++) {
    glActiveTexture(GL_TEXTURE0 + i);
    std::string number;
    std::string name = _textures[i].type;
    if (name == "texture_diffuse") {
      number = std::to_string(diffuseNr++);
    } else if (name == "texture_specular") {
      number = std::to_string(specularNr++);
    }
    shader.setInt((name + number).c_str(), i);
    // shader.setFloat("material." + name + number, _textures[i].id); //if using material uniform
    glBindTexture(GL_TEXTURE_2D, _textures[i].id);
  }

  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
  //std::cout << _indices.size() << std::endl;
  glBindVertexArray(0);

  glActiveTexture(GL_TEXTURE0);
}
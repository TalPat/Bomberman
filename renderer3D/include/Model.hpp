#ifndef MODEL_HPP
#define MODEL_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Shader.hpp"
#include "Mesh.hpp"

class Model
{
private:
  std::vector<Mesh> _meshes;
  std::vector<Texture_st> textures_loaded;
  std::string _directory;
  void processNode(aiNode* node, const aiScene* scene);
  Mesh processMesh(aiMesh* mesh, const aiScene* scene);
  std::vector<Texture_st> loadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName);
  unsigned int textureFromfile(const char *path, const std::string &directory, bool gamma = false);
public:
  Model(std::string path);
  ~Model();
  void draw(Shader shader);
};

#endif
#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Shader.hpp"
#include "Mesh.hpp"
#include "Animation.hpp"

class Square
{
private:
	std::vector<Mesh> _meshes;
	std::vector<Texture_st> textures_loaded;
	std::string _directory;
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture_st> loadMaterialTextures(aiMaterial *material, aiTextureType type, std::string typeName);
	unsigned int textureFromfile(const char *path);
	Animation _animation;
	unsigned int VAO, VBO, EBO, textureId;

public:
	Square(std::string path);
	~Square();
	void draw(Shader shader);
};

#endif

#ifndef GUICHAR_HPP
#define GUICHAR_HPP

#include <glm/glm.hpp>
#include "Shader.hpp"
#include <vector>
#include <map>

class GuiChar
{
private:
	unsigned int VAO, VBO, EBO, textureId;

public:
	GuiChar(std::string path);
	~GuiChar();

	void draw(Shader shader);
	unsigned int textureFromFile(const char *path);
};

#endif
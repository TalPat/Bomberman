#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
private:
  /* data */
public:
  //Program ID
  unsigned int ID;

  Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
  ~Shader();

  //use or activate shader
  void use();


  //utility uniform functions
  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
  void setMat4(const std::string &name, glm::mat4 value) const;
};

#endif
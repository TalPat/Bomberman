#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <GameState.hpp>
#include <Shader.hpp>
#include <Model.hpp>
#include <Camera.hpp>

enum modelNames {
  breakable, unbreakable, player, bomb, balloon, robot
};

struct Model_st {
  Model* model;
  glm::vec3 initialPos;
  glm::vec4 initialRot;
  glm::vec3 initialScale;
};

class Renderer
{
private:
  std::vector<Model_st> _models;
  Shader* _shader;
  Camera* _camera;
public:
  Renderer(/* args */);
  ~Renderer();
  void init();
  void render(sf::Window &window, const GameState &state);
};


#endif
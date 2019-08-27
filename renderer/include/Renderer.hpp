#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <GameState.hpp>
#include "../src/Shader.hpp"
#include "../src/Model.hpp"
#include "../src/Camera.hpp"

enum modelNames {
  breakableModel, unbreakableModel, playerModel, bombModel, flameModel, balloonModel, robotModel
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
	void player(sf::RenderWindow &window, const GameState &state);
	void map(sf::RenderWindow &window, const GameState &state);
  void enemy(sf::RenderWindow &window, const GameState &state);
public:
  Renderer(/* args */);
  ~Renderer();
  void init();
  void render(sf::RenderWindow &window, const GameState &state);
};


#endif
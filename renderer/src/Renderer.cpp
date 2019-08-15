#include "Renderer.hpp"
#include <iostream>

Renderer::Renderer(/* args */) {
}

Renderer::~Renderer() {
}

void Renderer::init() {
  // Enable glew
  GLenum err = glewInit();
  if (GLEW_OK != err) {
    std::cout << "failed to init GLEW: " << glewGetErrorString(err) << std::endl;
    throw ("GLEW failed");
  }
  std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
  glEnable(GL_DEPTH_TEST);
  glViewport(0, 0, 800, 800); //need to assign width and height possibly move to render

  //Wireframing
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  //Load objects into vram

  Model_st modelLoad;

  modelLoad.model = new Model("../../renderer/res/models/box/wall.obj");
  modelLoad.initialPos = glm::vec3(0.0f);
  modelLoad.initialRot = glm::vec4(0.0f);
  modelLoad.initialScale = glm::vec3(0.1f);
  _models.push_back(modelLoad);
  modelLoad.model = new Model("../../renderer/res/models/wall/wall.obj");
  modelLoad.initialPos = glm::vec3(0.0f);
  modelLoad.initialRot = glm::vec4(0.0f);
  modelLoad.initialScale = glm::vec3(0.1f);
  _models.push_back(modelLoad);

  modelLoad.model = new Model("../../renderer/res/models/nanosuit/nanosuit.obj");
  modelLoad.initialPos = glm::vec3(0.0f);
  modelLoad.initialRot = glm::vec4(0.0f);
  modelLoad.initialScale = glm::vec3(0.1f);
  _models.push_back(modelLoad);

  //compile shader programs
  _shader = new Shader("../../renderer/res/shaders/vertexShader.glsl", "../../renderer/res/shaders/fragmentShader.glsl");

  //build camera
  _camera = new Camera(glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 180.0f, 0.0f);
}

void Renderer::render(sf::Window &window, const GameState &state) {

	//std::cout << &window <<std::endl;
  glViewport(0, 0, 800, 600); //build size sampling function
  glClearColor(0.3f, 0.3f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _shader->use();



  // Map
	const Map &map = state.map;
	const sf::Vector2i &mapSize = map.size();
	Tile tile;
	for (int y = 0; y < mapSize.y; y++)
	{
		for (int x = 0; x < mapSize.x; x++)
		{
			sf::Vector2i cellPosition(x, y);
			tile = map.tileAt(cellPosition);
			if (tile != Tile::Clear)
			{
        glm::mat4 model = glm::mat4(1.0f);
        modelNames name;

				switch (tile)
				{
				case Tile::Solid:
          name = unbreakable;
					break;
				case Tile::Destructible:
					name = breakable;
					break;
				default:
					break;
				}
        model = glm::translate(model, _models[name].initialPos + glm::vec3(cellPosition.x, 0.0f, cellPosition.y));
        model = glm::scale(model, _models[name].initialScale);
        //model = glm::rotate(model, glm::radians(_models[name].initialRot.z), glm::vec3(_models[name].initialRot));
        _shader->setMat4("model", model);
        _models[name].model->draw(*_shader);
			}
		}
	}

	// Player
  glm::mat4 model = glm::mat4(1.0f);
	sf::Vector2f playerPosition(state.player.position());
	playerPosition -= sf::Vector2f(0.5, 0.5);
  model = glm::translate(model, _models[player].initialPos + glm::vec3(playerPosition.x, 0.0f, playerPosition.y));
  model = glm::scale(model, _models[player].initialScale);
  model = glm::rotate(model, glm::radians(_models[player].initialRot.z), glm::vec3(_models[player].initialRot));
  _shader->setMat4("model", model);
  _models[player].model->draw(*_shader);

  _camera->setPosition(glm::vec3(playerPosition.x, 20.0f, playerPosition.y + 20.0f));
  _camera->setYaw(270.0f);
  _camera->setPitch(-45.0f);

  window.display();
}

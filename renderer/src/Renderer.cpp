#include "Renderer.hpp"
#include <iostream>

Renderer::Renderer(/* args */)
{
}

Renderer::~Renderer()
{
}

void Renderer::init()
{
	// Enable glew
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cout << "failed to init GLEW: " << glewGetErrorString(err) << std::endl;
		throw("GLEW failed");
	}
	std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
	glEnable(GL_DEPTH_TEST);

	//Wireframing
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Load objects into vram
	Model_st modelLoad;

	modelLoad.model = new Model("../../renderer/res/models/box/wall.obj"); //breakable
	modelLoad.initialPos = glm::vec3(0.0f, 0.5f, 0.0f);
	modelLoad.initialRot = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
	modelLoad.initialScale = glm::vec3(0.5f);
	_models.push_back(modelLoad);

	modelLoad.model = new Model("../../renderer/res/models/wall/wall.obj"); //unbreakable
	modelLoad.initialPos = glm::vec3(0.0f, 0.5f, 0.0f);
	modelLoad.initialRot = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
	modelLoad.initialScale = glm::vec3(0.5f);
	_models.push_back(modelLoad);

	modelLoad.model = new Model("../../renderer/res/models/cowboy/model.dae"); //player
	modelLoad.initialPos = glm::vec3(0.0f);
	modelLoad.initialRot = glm::vec4(1.0f, 0.0f, 0.0f, 270.0f);
	modelLoad.initialScale = glm::vec3(0.2f);
	_models.push_back(modelLoad);

	modelLoad.model = new Model("../../renderer/res/models/ubomb/untitled.obj"); //bomb
	modelLoad.initialPos = glm::vec3(0.0f);
	modelLoad.initialRot = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
	modelLoad.initialScale = glm::vec3(0.1f);
	_models.push_back(modelLoad);

	modelLoad.model = new Model("../../renderer/res/models/giraffe/10021_Giraffe_v04.obj"); //flame
	modelLoad.initialPos = glm::vec3(0.0f);
	modelLoad.initialRot = glm::vec4(1.0f, 0.0f, 0.0f, 270.0f);
	modelLoad.initialScale = glm::vec3(0.01f);
	_models.push_back(modelLoad);

	modelLoad.model = new Model("../../renderer/res/models/giraffe/10021_Giraffe_v04.obj"); //balloon
	modelLoad.initialPos = glm::vec3(0.0f);
	modelLoad.initialRot = glm::vec4(1.0f, 0.0f, 0.0f, 270.0f);
	modelLoad.initialScale = glm::vec3(0.01f);
	_models.push_back(modelLoad);

	//compile shader programs
	_shader = new Shader("../../renderer/res/shaders/vertexShader.glsl", "../../renderer/res/shaders/fragmentShader.glsl");

	//build camera
	_camera = new Camera(glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 180.0f, 0.0f);

	//particles
	Swarm swarm;
	square = new Square("../../renderer/src/Flame_Particle.png");
}

void Renderer::player(sf::RenderWindow &window, const GameState &state)
{
	glm::mat4 model = glm::mat4(1.0f);
	sf::Vector2f playerPosition(state.player.position());
	playerPosition -= sf::Vector2f(0.5, 0.5);

	model = glm::translate(model, _models[playerModel].initialPos + glm::vec3(playerPosition.x, 0.0f, playerPosition.y));

	model = _models[playerModel].model->getAnimation().orientation(model, glm::vec2(playerPosition.x, playerPosition.y)); //simple animation. generate class to manage
	model = _models[playerModel].model->getAnimation().pulse(model, 10, 3);												  //simple animation. generate class to manage

	model = glm::scale(model, _models[playerModel].initialScale);
	model = glm::rotate(model, glm::radians(_models[playerModel].initialRot.w), glm::vec3(_models[playerModel].initialRot));
	_shader->setMat4("model", model);
	_models[playerModel].model->draw(*_shader);
}

void Renderer::map(sf::RenderWindow &window, const GameState &state)
{
	const Map &map = state.map;
	const sf::Vector2i &mapSize = map.size();
	Particle *pParticles = swarm.getParticles();
	Tile tile;
	swarm.update();
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
					name = unbreakableModel;
					model = glm::translate(model, _models[name].initialPos + glm::vec3(cellPosition.x, 0.0f, cellPosition.y));
					break;
				case Tile::Destructible:
					name = breakableModel;
					model = glm::translate(model, _models[name].initialPos + glm::vec3(cellPosition.x, 0.0f, cellPosition.y));
					break;
				case Tile::Bomb:
					name = bombModel;
					model = glm::translate(model, _models[name].initialPos + glm::vec3(cellPosition.x, 0.0f, cellPosition.y));
					model = _models[bombModel].model->getAnimation().pulse(model, 100, 30); //simple animation. generate class to manage
					break;
				case Tile::Flame:
					for (int a = 0; a < swarm.NPARTICLES; a++)
					{
						Particle points = pParticles[a];
						glm::mat4 model = glm::mat4(1.0f);
						model = glm::translate(model, glm::vec3(x + points.m_x, points.m_y, y + points.m_z));
						model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
						model = glm::rotate(model ,1.5708f, glm::vec3(0.0f, 1.0f, 0.0f));
						_shader->setMat4("model", model);
						square->draw(*_shader);
					}
					break;
				default:
					break;
				}
				model = glm::scale(model, _models[name].initialScale);
				model = glm::rotate(model, glm::radians(_models[name].initialRot.w), glm::vec3(_models[name].initialRot));
				_shader->setMat4("model", model);
				_models[name].model->draw(*_shader);
			}
		}
	}
}

void Renderer::enemy(sf::RenderWindow &window, const GameState &state)
{
	glm::mat4 model = glm::mat4(1.0f);
	sf::Vector2f enemyPosition(state.enemy.position());
	enemyPosition -= sf::Vector2f(0.5, 0.5);

	model = glm::translate(model, _models[balloonModel].initialPos + glm::vec3(enemyPosition.x, 0.0f, enemyPosition.y));

	model = _models[balloonModel].model->getAnimation().orientation(model, glm::vec2(enemyPosition.x, enemyPosition.y)); //simple animation. generate class to manage
	model = _models[balloonModel].model->getAnimation().floating(model);												 //simple animation. generate class to manage

	model = glm::scale(model, _models[balloonModel].initialScale);
	model = glm::rotate(model, glm::radians(_models[balloonModel].initialRot.w), glm::vec3(_models[balloonModel].initialRot));
	_shader->setMat4("model", model);
	_models[balloonModel].model->draw(*_shader);
}

void Renderer::render(sf::RenderWindow &window, const GameState &state)
{
	sf::Vector2u size = window.getSize();
	glViewport(0, 0, size.x, size.y);
	glClearColor(0.3f, 0.3f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_shader->use();
	glm::mat4 projection = glm::perspective(glm::radians(_camera->getZoom()), (float)size.x / (float)size.y, 0.1f, 100.0f);
	glm::mat4 view = _camera->getViewMatrix();
	_shader->setMat4("projection", projection);
	_shader->setMat4("view", view);

	map(window, state);
	player(window, state);
	enemy(window, state);

	sf::Vector2f playerPosition(state.player.position());
	playerPosition -= sf::Vector2f(0.5, 0.5);
	_camera->setPosition(glm::vec3(playerPosition.x, 5.0f, playerPosition.y + 5.0f));
	_camera->setYaw(270.0f);
	_camera->setPitch(-45.0f);

	window.display();
}

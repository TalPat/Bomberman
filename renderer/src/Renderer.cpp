#include "Renderer.hpp"
#include <iostream>

Renderer::Renderer(/* args */)
{
	fontMap = {
			{'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9}, {' ', 10}, {'a', 11}, {'b', 12}, {'c', 13}, {'d', 14}, {'e', 15}, {'f', 16}, {'g', 17}, {'h', 18}, {'i', 19}, {'j', 20}, {'k', 21}, {'l', 22}, {'m', 23}, {'n', 24}, {'o', 25}, {'p', 26}, {'q', 27}, {'r', 28}, {'s', 29}, {'t', 30}, {'u', 31}, {'v', 32}, {'w', 33}, {'x', 34}, {'y', 35}, {'z', 36}};
}

Renderer::~Renderer()
{
}

void Renderer::loadFont()
{
	for (size_t i = 0; i < 10; i++)
	{
		_characters.push_back(new GuiChar(std::string(CHARACTER_DIR) + "/" + std::string(1, '0' + i) + ".png"));
	}
	_characters.push_back(new GuiChar(std::string(CHARACTER_DIR) + "/white.png"));
	for (size_t i = 0; i < 26; i++)
	{
		_characters.push_back(new GuiChar(std::string(CHARACTER_DIR) + "/" + std::string(1, 'A' + i) + ".png"));
	}
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
	//load fonts
	loadFont();

	//Load objects into vram
	Model_st modelLoad;

	modelLoad.model = new Model(std::string(MODEL_DIR) + "/box/wall.obj"); //breakable
	modelLoad.initialPos = glm::vec3(0.0f, 0.5f, 0.0f);
	modelLoad.initialRot = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
	modelLoad.initialScale = glm::vec3(0.5f);
	_models.push_back(modelLoad);

	modelLoad.model = new Model(std::string(MODEL_DIR) + "/wall/wall.obj"); //unbreakable
	modelLoad.initialPos = glm::vec3(0.0f, 0.5f, 0.0f);
	modelLoad.initialRot = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
	modelLoad.initialScale = glm::vec3(0.5f);
	_models.push_back(modelLoad);

	modelLoad.model = new Model(std::string(MODEL_DIR) + "/playerHead/untitled.obj"); //bomb
	modelLoad.initialPos = glm::vec3(0.0f, 0.5f, 0.0f);
	modelLoad.initialRot = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
	modelLoad.initialScale = glm::vec3(0.08f);
	_models.push_back(modelLoad);

	modelLoad.model = new Model(std::string(MODEL_DIR) + "/ubomb/untitled.obj"); //bomb
	modelLoad.initialPos = glm::vec3(0.0f);
	modelLoad.initialRot = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
	modelLoad.initialScale = glm::vec3(0.1f);
	_models.push_back(modelLoad);

	modelLoad.model = new Model(std::string(MODEL_DIR) + "/giraffe/10021_Giraffe_v04.obj"); //flame
	modelLoad.initialPos = glm::vec3(0.0f);
	modelLoad.initialRot = glm::vec4(1.0f, 0.0f, 0.0f, 270.0f);
	modelLoad.initialScale = glm::vec3(0.01f);
	_models.push_back(modelLoad);

	modelLoad.model = new Model(std::string(MODEL_DIR) + "/pig/pignew.dae"); //pig
	modelLoad.initialPos = glm::vec3(0.0f);
	modelLoad.initialRot = glm::vec4(1.0f, 1.0f, 1.0f, 240.0f);
	modelLoad.initialScale = glm::vec3(0.06f);
	_models.push_back(modelLoad);

	modelLoad.model = new Model(std::string(MODEL_DIR) + "/robot/tankbot.dae"); //robot
	modelLoad.initialPos = glm::vec3(0.0f);
	modelLoad.initialRot = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
	modelLoad.initialScale = glm::vec3(0.04f);
	_models.push_back(modelLoad);

	modelLoad.model = new Model(std::string(MODEL_DIR) + "/ghost/Ghost.obj"); //ghost
	modelLoad.initialPos = glm::vec3(0.0f);
	modelLoad.initialRot = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
	modelLoad.initialScale = glm::vec3(0.2f);
	_models.push_back(modelLoad);

	modelLoad.model = new Model(std::string(MODEL_DIR) + "/shoe/shoel.obj"); //shoel
	modelLoad.initialPos = glm::vec3(-0.2f, 0.0f, 0.0f);
	modelLoad.initialRot = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
	modelLoad.initialScale = glm::vec3(0.06f);
	_models.push_back(modelLoad);

	modelLoad.model = new Model(std::string(MODEL_DIR) + "/shoe/shoer.obj"); //shoer
	modelLoad.initialPos = glm::vec3(0.2f, 0.0f, 0.0f);
	modelLoad.initialRot = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
	modelLoad.initialScale = glm::vec3(0.06f);
	_models.push_back(modelLoad);

	square = new Square(std::string(SPRITE_DIR) + "/tile1.png");

	//compile shader programs
	_shader = new Shader((std::string(SHADER_DIR) + "/vertexShader.glsl").c_str(), (std::string(SHADER_DIR) + "/fragmentShader.glsl").c_str());
	_textShader = new Shader((std::string(SHADER_DIR) + "/textv.glsl").c_str(), (std::string(SHADER_DIR) + "/textf.glsl").c_str());

	//build camera
	_camera = new Camera(glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 180.0f, 0.0f);
}

void Renderer::player(sf::RenderWindow &window, const GameState &state)
{
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 shoelModel = glm::mat4(1.0f);
	glm::mat4 shoerModel = glm::mat4(1.0f);
	sf::Vector2f playerPosition(state.player.position());
	playerPosition -= sf::Vector2f(0.5, 0.5);

	_models[shoel].model->getAnimation().setDeltas(glm::vec2(playerPosition.x, playerPosition.y));
	_models[shoer].model->getAnimation().setDeltas(glm::vec2(playerPosition.x, playerPosition.y));
	_models[playerModel].model->getAnimation().setDeltas(glm::vec2(playerPosition.x, playerPosition.y));

	model = glm::translate(model, _models[playerModel].initialPos + glm::vec3(playerPosition.x, 0.0f, playerPosition.y));
	shoelModel = glm::translate(shoelModel, glm::vec3(playerPosition.x, 0.0f, playerPosition.y));
	shoerModel = glm::translate(shoerModel, glm::vec3(playerPosition.x, 0.0f, playerPosition.y));

	model = _models[playerModel].model->getAnimation().orientation(model, glm::vec2(playerPosition.x, playerPosition.y)); //simple animation. generate class to manage
	model = _models[playerModel].model->getAnimation().waddle(model);
	shoelModel = _models[shoel].model->getAnimation().orientation(shoelModel, glm::vec2(playerPosition.x, playerPosition.y));
	shoelModel = _models[shoel].model->getAnimation().leftFoot(shoelModel);
	shoerModel = _models[shoer].model->getAnimation().orientation(shoerModel, glm::vec2(playerPosition.x, playerPosition.y));
	shoerModel = _models[shoer].model->getAnimation().rightFoot(shoerModel);

	model = _models[playerModel].model->getAnimation().pulse(model, 10, 3);																								//simple animation. generate class to manage

	model = glm::scale(model, _models[playerModel].initialScale);
	model = glm::rotate(model, glm::radians(_models[playerModel].initialRot.w), glm::vec3(_models[playerModel].initialRot));
	_shader->setMat4("model", model);
	_models[playerModel].model->draw(*_shader);

	shoelModel = glm::translate(shoelModel, _models[shoel].initialPos);
	shoelModel = glm::scale(shoelModel, _models[shoel].initialScale);
	shoelModel = glm::rotate(shoelModel, glm::radians(_models[shoel].initialRot.w), glm::vec3(_models[shoel].initialRot));
	_shader->setMat4("model", shoelModel);
	_models[shoel].model->draw(*_shader);

	shoerModel = glm::translate(shoerModel, _models[shoer].initialPos);
	shoerModel = glm::scale(shoerModel, _models[shoer].initialScale);
	shoerModel = glm::rotate(shoerModel, glm::radians(_models[shoer].initialRot.w), glm::vec3(_models[shoer].initialRot));
	_shader->setMat4("model", shoerModel);
	_models[shoer].model->draw(*_shader);
}

void Renderer::map(sf::RenderWindow &window, const GameState &state)
{
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
																																									// model = _models[bombModel].model->getAnimation().spin(model, 3, glm::vec3(0.0f, 1.0f, 0.0f)); //simple animation. generate class to manage
					break;
				case Tile::Flame:
					name = flameModel;
					model = glm::translate(model, _models[name].initialPos + glm::vec3(cellPosition.x, 0.0f, cellPosition.y));
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
	_models[pigModel].model->getAnimation().setDeltas(glm::vec2(enemyPosition.x, enemyPosition.y));

	model = glm::translate(model, _models[pigModel].initialPos + glm::vec3(enemyPosition.x, 0.0f, enemyPosition.y));

	model = _models[pigModel].model->getAnimation().orientation(model, glm::vec2(enemyPosition.x, enemyPosition.y)); //simple animation. generate class to manage
	//model = _models[balloonModel].model->getAnimation().floating(model); //simple animation. generate class to manage
	model = _models[pigModel].model->getAnimation().waddle(model);

	model = glm::scale(model, _models[pigModel].initialScale);
	model = glm::rotate(model, glm::radians(_models[pigModel].initialRot.w), glm::vec3(_models[pigModel].initialRot));
	_shader->setMat4("model", model);
	_models[pigModel].model->draw(*_shader);
}

void Renderer::render(sf::RenderWindow &window, const GameState &state)
{
	window.setActive(true);
	sf::Vector2u size = window.getSize();
	glViewport(0, 0, size.x, size.y);
	glClearColor(0.3f, 0.3f, 5.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//frame counter
	writeLine(window, "FPS "+std::to_string((int)(1/_clock.getElapsedTime().asSeconds())), sf::Vector3i(10,20,50), sf::Vector2f(-1.0f,-1.0f), 0.2f);
	_clock.restart();

	sf::Vector2f playerPosition(state.player.position());
	playerPosition -= sf::Vector2f(0.5, 0.5);
	_camera->setPosition(glm::vec3(playerPosition.x, 5.0f, playerPosition.y + 5.0f));
	_camera->setYaw(270.0f);
	_camera->setPitch(-45.0f);

	_shader->use();
	glm::mat4 projection = glm::perspective(glm::radians(_camera->getZoom()), (float)size.x / (float)size.y, 0.1f, 100.0f);
	glm::mat4 view = _camera->getViewMatrix();
	_shader->setMat4("projection", projection);
	_shader->setMat4("view", view);

	/*drawing tiles with square object test only*/
	for (size_t i = 0; i < 20; i++)
	{
		for (size_t j = 0; j < 20; j++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(i, 0.0f, j));
			_shader->setMat4("model", model);
			square->draw(*_shader);
		}
		
	}
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(10, -1.0f, 10));
	model = glm::scale(model, glm::vec3(20.f));
	_shader->setMat4("model", model);
	square->draw(*_shader);
	/*endoftest*/

	map(window, state);
	player(window, state);
	enemy(window, state);

	window.display();
}

void Renderer::writeLine(sf::RenderWindow &window, std::string string, sf::Vector3i color, sf::Vector2f pos, float scale)
{
	_textShader->use();

	float offset = 0.0f;
	sf::Vector2u size = window.getSize();
	float ratio = (float)(size.y)/size.x;
	float stride = 0.35 * scale * ratio / 1.4;
	glm::mat4 posMat = glm::mat4(1.0f);
	glm::mat4 scaleMat = glm::mat4(1.0f);

	posMat = glm::translate(posMat, glm::vec3(pos.x, pos.y, 0.0f));
	scaleMat = glm::scale(scaleMat, glm::vec3(scale * ratio / 1.4, scale, scale));

	_textShader->setVec3("textColor", glm::vec3((float)(color.x)/255, (float)(color.y)/255, (float)(color.z)/255));

	for (char &c : string)
	{
		c = std::tolower(c);
		_textShader->setMat4("posMat", posMat);
		_textShader->setMat4("scaleMat", scaleMat);
		_characters[fontMap[c]]->draw(*_textShader);
		posMat = glm::translate(posMat, glm::vec3(stride, 0.0f, 0.0f));
	}

	//window.display(); //remove if function no longer called outside of renderer class
}

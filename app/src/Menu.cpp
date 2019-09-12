#include "./Menu.hpp"

Menu::Menu() {}

Menu::~Menu() {}

void Menu::init(Renderer &renderer)
{
	this->_renderer = &renderer;

	Model_st modelLoad;

	modelLoad.model = new Model("../../renderer/res/models/wall/wall.obj"); //unbreakable
	modelLoad.initialPos = glm::vec3(0.0f, 0.5f, 0.0f);
	modelLoad.initialRot = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
	modelLoad.initialScale = glm::vec3(0.5f);
	_wallModel = modelLoad;
}

void Menu::render(sf::RenderWindow &window, const GameState &state)
{

	sf::Vector2u size = window.getSize();
	glViewport(0, 0, size.x, size.y);
	glClearColor(0.3f, 0.3f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	this->_renderer->shader()->use();
	glm::mat4 projection = glm::perspective(glm::radians(this->_renderer->camera()->getZoom()), (float)size.x / (float)size.y, 0.1f, 100.0f);
	glm::mat4 view = this->_renderer->camera()->getViewMatrix();
	this->_renderer->shader()->setMat4("projection", projection);
	this->_renderer->shader()->setMat4("view", view);

	sf::Vector2f playerPosition(state.player.position());
	playerPosition -= sf::Vector2f(0.5, 0.5);
	this->_renderer->camera()->setPosition(glm::vec3(playerPosition.x, 5.0f, playerPosition.y + 5.0f));
	this->_renderer->camera()->setYaw(270.0f);
	this->_renderer->camera()->setPitch(-45.0f);





	sf::Vector2i cellPosition(1, 1);
	glm::mat4 model = glm::mat4(1.0f);
	modelNames name;
	name = unbreakableModel;
	model = glm::translate(model, this->_wallModel.initialPos + glm::vec3(cellPosition.x, 0.0f, cellPosition.y));

	model = glm::scale(model, this->_wallModel.initialScale);
	model = glm::rotate(model, glm::radians(this->_wallModel.initialRot.w), glm::vec3(this->_wallModel.initialRot));
	this->_renderer->shader()->setMat4("model", model);
	this->_wallModel.model->draw(*this->_renderer->shader());

	window.display();
}

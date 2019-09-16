#include "./Menu.hpp"

Menu::Menu() {}

Menu::~Menu() {}

void Menu::init(Renderer &renderer)
{
	this->_renderer = &renderer;
	this->_shader = renderer.shader();
	this->_camera = renderer.camera();

	Model_st modelLoad;

	modelLoad.model = new Model((std::string(MODELS_DIR) + "/wall/wall.obj"));
	modelLoad.initialPos = glm::vec3(0.0f, 0.0f, 0.0f);
	modelLoad.initialRot = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
	modelLoad.initialScale = glm::vec3(0.5f);
	_wallModel = modelLoad;

	this->selected = MenuOption::Start;
	this->menuItems.push_back(MenuItem(-2, "Start", MenuOption::Start));
	this->menuItems.push_back(MenuItem(0, "Controls", MenuOption::Controls));
	this->menuItems.push_back(MenuItem(2, "Exit", MenuOption::Exit));
}

void Menu::drawMenuBlock(MenuItem &item)
{
	sf::Vector2i cellPosition(1, 1);
	glm::mat4 model = glm::mat4(1.0f);
	modelNames name;
	name = unbreakableModel;
	model = glm::translate(model, this->_wallModel.initialPos + glm::vec3(cellPosition.x + item.offset, 0.0f, cellPosition.y));

	bool selected = (this->selected == item.option);
	glm::vec3 scale(0.5f + selected * 0.2f);
	model = glm::scale(model, scale);
	model = glm::rotate(model, glm::radians(this->_wallModel.initialRot.w), glm::vec3(this->_wallModel.initialRot));
	this->_shader->setMat4("model", model);
	this->_wallModel.model->draw(*this->_shader);
}

void Menu::drawMenuText(sf::RenderWindow &window, MenuItem &item)
{
	sf::Vector3i color = sf::Vector3i(10, 20, 50);
	sf::Vector2f startLocation = sf::Vector2f(item.offset / 4.0f, -0.05f);
	float scale = 0.15f;
	this->_renderer->writeLine(window, item.text, color, startLocation, scale);
}

MenuOption Menu::handleInput(std::vector<EngineEvent> &actions)
{
	for (EngineEvent action : actions)
	{
		switch (action)
		{
		case EngineEvent::move_left:
			this->menuLeft();
			break;
		case EngineEvent::move_right:
			this->menuRight();
			break;
		case EngineEvent::place_bomb:
			return this->select();
		default:	
			return MenuOption::None;
			break;
		}
	}

	return MenuOption::None;
}

void Menu::menuLeft()
{
	if (this->selected > 0)
		this->selected = MenuOption(this->selected - 1);
}

void Menu::menuRight()
{
	if (this->selected < this->menuItems.size() - 1)
		this->selected = MenuOption(this->selected + 1);
}

MenuOption Menu::select()
{
	switch(this->selected)
	{
	case MenuOption::Controls:
		std::cout << "Controls" << std::endl;
		return MenuOption::None;
		break;
	default:
		return this->selected;
		break;
	}
}

MenuOption Menu::render(sf::RenderWindow &window, std::vector<EngineEvent> &actions)
{
	sf::Vector2u size = window.getSize();
	glViewport(0, 0, size.x, size.y);
	glClearColor(0.3f, 0.3f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	this->_shader->use();
	glm::mat4 projection = glm::perspective(glm::radians(this->_camera->getZoom()), (float)size.x / (float)size.y, 0.1f, 100.0f);
	glm::mat4 view = this->_camera->getViewMatrix();
	this->_shader->setMat4("projection", projection);
	this->_shader->setMat4("view", view);

	sf::Vector2f cameraPosition(1.5, 1.5);
	cameraPosition -= sf::Vector2f(0.5, 0.5);
	this->_camera->setPosition(glm::vec3(cameraPosition.x, 0.0f, cameraPosition.y + 4.0f));
	this->_camera->setYaw(270.0f);
	this->_camera->setPitch(0.0f);
	
	for (MenuItem item : this->menuItems)
	{
		this->drawMenuBlock(item);
	}

	for (MenuItem item : this->menuItems)
	{
		this->drawMenuText(window, item);
	}

	window.display();

	return this->handleInput(actions);
}

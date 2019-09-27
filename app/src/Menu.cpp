#include "./Menu.hpp"

Menu::Menu() {}

Menu::~Menu() {}

void Menu::init(Renderer &renderer, std::vector<MenuItem> &items)
{
	this->_renderer = &renderer;
	this->_shader = renderer.shader();
	this->_camera = renderer.camera();

	this->menuItems = items;
}

void Menu::drawMenuText(sf::RenderWindow &window, MenuItem &item)
{
	std::string text = item.text;
	sf::Vector3i color = sf::Vector3i(10, 20, 50);
	sf::Vector2f startLocation = sf::Vector2f(-0.5f, item.offset / 4.0f);
	float scale = 0.15f + item.selected * 0.05f;

	if (item.selected)
		color = sf::Vector3i(250, 250, 250);

	this->_renderer->writeLine(window, item.text, color, startLocation, scale);
}

MenuAction Menu::handleInput(std::vector<EngineEvent> &actions)
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
		case EngineEvent::move_up:
			this->menuLeft();
			break;
		case EngineEvent::move_down:
			this->menuRight();
			break;
		case EngineEvent::place_bomb:
			return this->select();
		default:	
			return MenuAction::Nothing;
			break;
		}
	}

	return MenuAction::Nothing;
}

void Menu::menuLeft()
{
	if (this->menuItems[0].selected)
		return;

	for (int i = 0; i < this->menuItems.size() - 1; i++)
	{
		if (this->menuItems[i + 1].selected)
		{
			this->menuItems[i].selected = true;
			this->menuItems[i + 1].selected = false;
			break;
		}
	}
}

void Menu::menuRight()
{
	for (int i = 0; i < this->menuItems.size() - 1; i++)
	{
		if (this->menuItems[i].selected)
		{
			this->menuItems[i].selected = false;
			this->menuItems[i + 1].selected = true;
			break;
		}
	}
}

MenuAction Menu::select()
{
	for (int i = 0; i < this->menuItems.size(); i++)
	{
		if (this->menuItems[i].selected)
			return this->menuItems[i].option;
	}

	return MenuAction::Nothing;
}

MenuAction Menu::render(sf::RenderWindow &window, std::vector<EngineEvent> &actions)
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
		this->drawMenuText(window, item);
	}

	window.display();

	return this->handleInput(actions);
}

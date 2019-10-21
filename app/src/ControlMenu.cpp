#include "./ControlMenu.hpp"

ControlMenu::ControlMenu() {}

ControlMenu::~ControlMenu() {}

void ControlMenu::init(Renderer &renderer, MenuAction backOption)
{
	this->_renderer = &renderer;
	this->_shader = renderer.shader();
	this->_camera = renderer.camera();
	this->backOption = backOption;

	this->menuItems = {
		MenuItem(3.0f, "Up", true, MenuAction::SetUpControl, Menu::keyStrings[Key::Up]),
		MenuItem(2.0f, "Down", false, MenuAction::SetDownControl, Menu::keyStrings[Key::Down]),
		MenuItem(1.0f, "Left", false, MenuAction::SetLeftControl, Menu::keyStrings[Key::Left]),
		MenuItem(-0.5f, "Right", false, MenuAction::SetRightControl, Menu::keyStrings[Key::Right]),
		MenuItem(-1.5f, "Bomb", false, MenuAction::SetBombControl, Menu::keyStrings[Key::Space]),
		MenuItem(-2.5f, "Back", false, MenuAction::ToSettingsMenu)
	};

	this->settingScreen = MenuItem(0, "Please select new key", false, MenuAction::Nothing);
}

void ControlMenu::displaySettingScreen(sf::RenderWindow &window)
{
	sf::Vector2u size = window.getSize();
	glViewport(0, 0, size.x, size.y);
	glClearColor(0.3f, 0.3f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	this->drawMenuText(window, this->settingScreen);

	window.display();
}

void ControlMenu::setControl(EngineEvent action, Key key)
{
	switch (action)
	{
	case EngineEvent::move_up:
		this->menuItems[0].additional = Menu::keyStrings[key];
		break;
	case EngineEvent::move_down:
		this->menuItems[1].additional = Menu::keyStrings[key];
		break;
	case EngineEvent::move_left:
		this->menuItems[2].additional = Menu::keyStrings[key];
		break;
	case EngineEvent::move_right:
		this->menuItems[3].additional = Menu::keyStrings[key];
		break;
	case EngineEvent::place_bomb:
		this->menuItems[4].additional = Menu::keyStrings[key];
		break;
	default:
		break;
	}
}

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
}

void ControlMenu::setControl(EngineEvent event)
{

}

#ifndef _ControlMenu_hpp_
#define _ControlMenu_hpp_

#include <Renderer.hpp>
#include <EngineEvent.hpp>

#include "./Menu.hpp"

#include <vector>

typedef sf::Keyboard::Key Key;

class ControlMenu : public Menu
{
private:
	MenuItem settingScreen;

public:
	ControlMenu();
	~ControlMenu();

	void init(Renderer &renderer, MenuAction backOption);
	void displaySettingScreen(sf::RenderWindow &window);
	void setControl(EngineEvent action, Key key);
};

#endif

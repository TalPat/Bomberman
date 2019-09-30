#ifndef _Menu_hpp_
#define _Menu_hpp_

#include <Renderer.hpp>
#include <EngineEvent.hpp>

#include "./Input.hpp"

#include <vector>

enum MenuAction
{
	StartGame,
	ToControlsMenu,
	ToSettingsMenu,
	ToResolutionMenu,
	ToMainMenu,
	SetResolution800,
	SetResolution1024,
	SetResolutionFullscreen,
	SetUpControl,
	SetDownControl,
	SetLeftControl,
	SetRightControl,
	SetBombControl,
	Exit,
	Nothing
};

struct MenuItem
{
	int offset;
	std::string text;
	std::string additional = "";
	bool selected;
	MenuAction option;

	MenuItem(float offset, std::string text, bool selected, MenuAction option)
		: offset(offset), text(text), selected(selected), option(option) {}
	
	MenuItem(float offset, std::string text, bool selected, MenuAction option, std::string additional)
		: offset(offset), text(text), selected(selected), option(option), additional(additional) {}
};

class Menu
{
private:
	Renderer *_renderer;
	Shader *_shader;
	Camera *_camera;

	std::vector<MenuItem> menuItems;
	MenuAction backOption;

	void drawMenuText(sf::RenderWindow &window, MenuItem &item);
	MenuAction handleInput(sf::RenderWindow &window);
	void menuLeft();
	void menuRight();
	MenuAction select();

public:
	Menu();
	~Menu();

	void init(Renderer &renderer, std::vector<MenuItem> &items, MenuAction backOption);
	MenuAction render(sf::RenderWindow &window);

	static std::map<Key, std::string> keyStrings;
};

#endif

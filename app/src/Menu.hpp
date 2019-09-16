#ifndef _Menu_hpp_
#define _Menu_hpp_

#include <Renderer.hpp>
#include <EngineEvent.hpp>

#include <vector>

enum MenuOption
{
	Start,
	Controls,
	Exit,
	None
};

struct MenuItem
{
	int offset;
	std::string text;
	MenuOption option;

	MenuItem(int offset, std::string text, MenuOption option)
		: offset(offset), text(text), option(option) {}
};

class Menu
{
private:
	Renderer *_renderer;
	Shader *_shader;
	Camera *_camera;
	Model_st _wallModel;

	std::vector<MenuItem> menuItems;
	MenuOption selected;

	void drawMenuBlock(MenuItem &item);
	void drawMenuText(sf::RenderWindow &window, MenuItem &item);
	MenuOption handleInput(std::vector<EngineEvent> &actions);
	void menuLeft();
	void menuRight();
	MenuOption select();

public:
	Menu();
	~Menu();

	void init(Renderer &renderer, std::vector<MenuItem> &items);
	MenuOption render(sf::RenderWindow &window, std::vector<EngineEvent> &actions);
};

#endif

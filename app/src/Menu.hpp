#ifndef _Menu_hpp_
#define _Menu_hpp_

#include <Renderer.hpp>
#include <EngineEvent.hpp>

#include <vector>

enum MenuAction
{
	StartGame,
	ToControlsMenu,
	ToMainMenu,
	Exit,
	Nothing
};

struct MenuItem
{
	int offset;
	std::string text;
	bool selected;
	MenuAction option;

	MenuItem(int offset, std::string text, bool selected, MenuAction option)
		: offset(offset), text(text), selected(selected), option(option) {}
};

class Menu
{
private:
	Renderer *_renderer;
	Shader *_shader;
	Camera *_camera;
	Model_st _wallModel;

	std::vector<MenuItem> menuItems;

	void drawMenuBlock(MenuItem &item);
	void drawMenuText(sf::RenderWindow &window, MenuItem &item);
	MenuAction handleInput(std::vector<EngineEvent> &actions);
	void menuLeft();
	void menuRight();
	MenuAction select();

public:
	Menu();
	~Menu();

	void init(Renderer &renderer, std::vector<MenuItem> &items);
	MenuAction render(sf::RenderWindow &window, std::vector<EngineEvent> &actions);
};

#endif

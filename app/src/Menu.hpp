#ifndef _Menu_hpp_
#define _Menu_hpp_

#include <Renderer.hpp>
#include <EngineEvent.hpp>

#include <vector>
#include <algorithm>

struct MenuItem
{
	int offset;
	std::string text;
	bool selected;

	MenuItem(int offset, std::string text, bool selected)
		: offset(offset), text(text), selected(selected) {}
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
	void handleInput(std::vector<EngineEvent> &actions);

public:
	Menu();
	~Menu();

	void init(Renderer &renderer);
	void render(sf::RenderWindow &window, std::vector<EngineEvent> &actions);
};

#endif

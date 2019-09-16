#ifndef _Menu_hpp_
#define _Menu_hpp_

#include <Renderer.hpp>

struct MenuItem
{
	int offset;
	std::string text;

	MenuItem(int offset, std::string text) : offset(offset), text(text) {}
};

class Menu
{
private:
	Renderer *_renderer;
	Shader *_shader;
	Camera *_camera;
	Model_st _wallModel;

	void drawMenuBlock(MenuItem &item);
	void drawMenuText(sf::RenderWindow &window, MenuItem &item);

public:
	Menu();
	~Menu();

	void init(Renderer &renderer);
	void render(sf::RenderWindow &window, const GameState &state);
};

#endif

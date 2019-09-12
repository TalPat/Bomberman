#ifndef _Menu_hpp_
#define _Menu_hpp_

#include <Renderer.hpp>

class Menu
{
private:
	Renderer *_renderer;
	Model_st _wallModel;

	void drawMenuItem(std::string text, int offset);

public:
	Menu();
	~Menu();

	void init(Renderer &renderer);
	void render(sf::RenderWindow &window, const GameState &state);
};

#endif

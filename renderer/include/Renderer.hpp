#ifndef _Renderer_hpp_
#define _Renderer_hpp_


#include "../../engine/include/Engine.hpp"
#include <SFML/Graphics.hpp>

class Renderer
{
public:
	void render(sf::RenderWindow &window, GameState &state);
    Renderer();
    ~Renderer();
};

#endif

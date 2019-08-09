#ifndef _Renderer_hpp_
#define _Renderer_hpp_

#include "interface/IRenderable.hpp"

#include <SFML/Graphics.hpp>

#include <vector>

class Renderer
{
public:
	void render(sf::RenderWindow &window, const std::vector<IRenderable *>);
};

#endif

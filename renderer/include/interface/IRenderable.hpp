#ifndef _IRenderable_hpp_
#define _IRenderable_hpp_

#include <SFML/Graphics.hpp>

class IRenderable
{
public:
	virtual ~IRenderable() {}

	virtual void render(sf::RenderWindow &ctx) = 0;
};

#endif

#ifndef _Player_hpp_
#define _Player_hpp_

#include <interface/IRenderable.hpp>

class Player : public IRenderable
{
public:
	virtual ~Player();

	virtual void render(sf::RenderWindow &ctx);
};

#endif

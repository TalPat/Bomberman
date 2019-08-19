#ifndef _Bombs_hpp_
#define _Bombs_hpp_

#include "Map.hpp"
#include "Player.hpp"

#include <list>

struct sBomb
{
	sf::Vector2i position;
	float timeLeft;
};

class Bombs
{
private:
	std::list<sBomb> _bombs;

public:
	// static int totalBombs;
	static int totalBombs;
	Bombs();
	void placeBomb(const Player &player, Map &map);
	void update(float deltaTime, Map &map);
};

#endif
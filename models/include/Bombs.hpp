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

struct sFlame
{
    sf::Vector2i position;
    float timeLeft;
};

class Bombs
{
private:
	std::list<sBomb> _bombs;
    std::list<sFlame> _flames;

public:
	Bombs();
	void placeBomb(const Player &player, Map &map);
    void placeFlame(sf::Vector2i pos, Map &map);
	void update(float deltaTime, Map &map);
};

#endif

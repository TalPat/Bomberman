#ifndef _Bombs_hpp_
#define _Bombs_hpp_

#include "Map.hpp"
#include "Player.hpp"
#include "Sound.hpp"

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
	static int bomb_range;
	static int max_bombs;
	
	Bombs();
	void clear(void);
	void placeBomb(const Player &player, Map &map);
	void placeFlame(sf::Vector2i pos, Map &map);
	void explode(Map &map, sf::Vector2i pos, sf::Vector2i dir, int range);
	void update(float deltaTime, Map &map, Player &player);
	void updateMap(Player &player, Map &map);

	std::string to_string();
	void from_string(std::istream &istream);
};

#endif

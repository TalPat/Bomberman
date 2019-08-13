#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/System.hpp>

#include <vector>

enum Tile
{
	Solid,
	Clear,
	Destructible,
};

class Map
{
private:
	sf::Vector2i size;
	// Consider the map size to be the internal size.
	// Its is redundant to specify borders when we know it will
	// be at the edge of the map
	std::vector<Tile> tiles;

public:
	Map();
	~Map();
};

#endif

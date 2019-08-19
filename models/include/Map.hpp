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
	sf::Vector2i _size;
	// Consider the map size to be the internal size.
	// Its is redundant to specify borders when we know it will
	// be at the edge of the map
	std::vector<Tile> _tiles;

public:
	Map();
	~Map();

	Tile tileAt(sf::Vector2i pos) const;
	void setTile(sf::Vector2i pos, Tile tile);
	const sf::Vector2i &size() const;
};

#endif

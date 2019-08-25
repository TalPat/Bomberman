#ifndef MAP_HPP
#define MAP_HPP

#include "./ICollider.hpp"

#include <SFML/System.hpp>
#include <vector>

enum Tile
{
	Solid,
	Clear,
	Destructible,
	Bomb,
	Flame,
};

class Map : public ICollider
{
private:
	sf::Vector2i _size;
	std::vector<Tile> _tiles;

public:
	Map();
	~Map();

    bool collide(const sf::Vector2f &pos, float radius) const;
	Tile tileAt(sf::Vector2i pos) const;
	void setTile(sf::Vector2i pos, Tile tile);
	const sf::Vector2i &size() const;
};

#endif

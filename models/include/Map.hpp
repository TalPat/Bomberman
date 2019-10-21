#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/System.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <sstream>

enum Tile
{
	Solid,
	Clear,
	Destructible,
	Bomb,
	BombClear,
	Flame,
};

class Map
{
private:
	sf::Vector2i _size;
	std::vector<Tile> _tiles;

public:
	Map();
	~Map();

	void init(int level);
	bool collide(const sf::Vector2f &pos, float hw, bool (*comp)(Tile)) const;
	bool lerpCollide(sf::Vector2f &pos, sf::Vector2f mv, float hw, bool (*comp)(Tile)) const;
	Tile tileAt(sf::Vector2i pos) const;
	void setTile(sf::Vector2i pos, Tile tile);
	const sf::Vector2i &size() const;

	std::string to_string();
	void from_string(std::istream &istream);
};

#endif
#include "../include/Map.hpp"

sf::Vector2i DEFAULT_SIZE(11, 11);

Map::Map()
	: _size(DEFAULT_SIZE),
	  _tiles(this->_size.x * this->_size.y, Tile::Clear)
{
	for (int y = 0; y < _size.y; y++)
	{
		for (int x = 0; x < _size.x; x++)
		{
			if (x % 2 == 0 && y % 2 == 0)
				this->_tiles[y * this->_size.x + x] = Tile::Solid;
		}
	}
}

Map::~Map()
{
}

Tile Map::tileAt(sf::Vector2i pos) const
{
	return this->_tiles[pos.y * this->_size.x + pos.x];
}

const sf::Vector2i &Map::size() const
{
	return this->_size;
}

#include "../include/Map.hpp"

sf::Vector2i DEFAULT_SIZE(11, 11);

Map::Map()
	: size(DEFAULT_SIZE),
	  tiles(this->size.x * this->size.y, Tile::Clear)
{
}

Map::~Map()
{
}

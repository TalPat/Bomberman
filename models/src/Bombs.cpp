#include "../include/Bombs.hpp"

#include <iostream>
#include <cmath>

const float FUSE_TIME = 2;
const float FLAME_TIME = 0.3;
const float BOMB_RANGE = 3; // TODO: change based on player powerups

Bombs::Bombs()
	: _bombs()
{
}

void Bombs::placeBomb(const Player &player, Map &map)
{
	sf::Vector2i playerCell(player.position());

	if (map.tileAt(playerCell) == Tile::Clear)
	{
		map.setTile(playerCell, Tile::BombClear);
		sBomb newBomb;
		newBomb.position = playerCell;
		newBomb.timeLeft = FUSE_TIME;

		this->_bombs.push_back(newBomb);
	}
}

void Bombs::updateMap(Player &player, Map &map)
{
	typedef sf::Vector2i v2i;
	typedef sf::Vector2f v2f;

	v2f pos(player.position());

	for (sBomb &bomb : this->_bombs)
	{
		if (map.tileAt(bomb.position) == Tile::BombClear)
		{
			float dx = bomb.position.x + 0.5 - player.position().x;
			float dy = bomb.position.y + 0.5 - player.position().y;
			float dist = sqrt((dx*dx) + (dy*dy));
			if (dist > 1.0)
			{
				map.setTile(bomb.position, Tile::Bomb);
			}
		}
	}	
}

void Bombs::update(float deltaTime, Map &map)
{
	for (sBomb &bomb : this->_bombs)
	{
		bomb.timeLeft -= deltaTime;
		// If current bomb is on a flame, detonate the bomb
		if (map.tileAt(bomb.position) == Tile::Flame)
		{
			bomb.timeLeft = -1;
		}
		if (bomb.timeLeft < 0)
		{
			this->placeFlame(bomb.position, map);
			this->bombExplodeDirection(bomb, map, sf::Vector2i(+1, 0));
			this->bombExplodeDirection(bomb, map, sf::Vector2i(-1, 0));
			this->bombExplodeDirection(bomb, map, sf::Vector2i(0, -1));
			this->bombExplodeDirection(bomb, map, sf::Vector2i(0, +1));
		}
	}
	this->_bombs.remove_if([](sBomb &bomb) { return bomb.timeLeft < 0; });

	for (sFlame &flame : this->_flames)
	{
		flame.timeLeft -= deltaTime;
		if (flame.timeLeft < 0)
		{
			map.setTile(flame.position, Tile::Clear);
		}
	}
	this->_flames.remove_if([](sFlame &flame) { return flame.timeLeft < 0; });
}

void Bombs::bombExplodeDirection(sBomb &bomb, Map &map, sf::Vector2i dir)
{
	sf::Vector2i pos = bomb.position;

	for (int i = 0; i < BOMB_RANGE + 1; ++i)
	{
		Tile tile = map.tileAt(pos + dir * i);
		if (tile != Tile::Solid)
		{
			this->placeFlame(pos + dir * i, map);
		}
		if (tile == Tile::Bomb || tile == Tile::Destructible || tile == Tile::Solid)
		{
			return;
		}
	}
}

void Bombs::placeFlame(sf::Vector2i pos, Map &map)
{
	if (map.tileAt(pos) != Tile::Solid)
	{
		map.setTile(pos, Tile::Flame);

		sFlame newFlame;
		newFlame.position = pos;
		newFlame.timeLeft = FLAME_TIME;
		this->_flames.push_back(newFlame);
	}
}

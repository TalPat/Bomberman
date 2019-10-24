#include "../include/Bombs.hpp"

#include <iostream>
#include <cmath>

int Bombs::bomb_range = 2;
int Bombs::max_bombs = 2;
const float FUSE_TIME = 2.5;
const float FLAME_TIME = 0.3;
const sf::Vector2i EAST(+1, 0);
const sf::Vector2i WEST(-1, 0);
const sf::Vector2i NORTH(0, -1);
const sf::Vector2i SOUTH(0, +1);

Bombs::Bombs()
	: _bombs()
{
}

void Bombs::clear(void)
{
	this->_bombs.remove_if([](sBomb &bomb) { return true; });
	this->_flames.remove_if([](sFlame &flame) { return true; });
}

void Bombs::placeBomb(const Player &player, Map &map)
{
	sf::Vector2i playerCell(player.position());

	if ( this->_bombs.size() < player.getMaxBombs() && map.tileAt(playerCell) == Tile::Clear)
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

void Bombs::update(float deltaTime, Map &map, Player &player)
{
	for (sBomb &bomb : this->_bombs)
	{
		bomb.timeLeft -= deltaTime;
		// If current bomb is on a flame, detonate the bomb
		if (bomb.timeLeft < 0)
		{
			Sound::playSound(boom);
			this->placeFlame(bomb.position, map);
			this->explode(map, bomb.position, EAST, player.getBombRange());
			this->explode(map, bomb.position, WEST, player.getBombRange());
			this->explode(map, bomb.position, NORTH, player.getBombRange());
			this->explode(map, bomb.position, SOUTH, player.getBombRange());
		}
		if (map.tileAt(bomb.position) == Tile::Flame)
		{
			bomb.timeLeft = -1;
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

void Bombs::explode(Map &map, sf::Vector2i pos, sf::Vector2i dir, int range)
{
	for (int i = 0; i < range + 1; ++i)
	{
		Tile tile = map.tileAt(pos + dir * i);
		if (tile != Tile::Solid)
		{
			this->placeFlame(pos + dir * i, map);
		}
		if (tile == Tile::Bomb)
		{
			auto vecEqual = [](sf::Vector2i a, sf::Vector2i b) {
				return ((a.x == b.x) && (a.y == b.y));
			};
			if (!vecEqual(-dir, EAST)) this->explode(map, pos + dir * i, EAST, range);
			if (!vecEqual(-dir, WEST)) this->explode(map, pos + dir * i, WEST, range);
			if (!vecEqual(-dir, NORTH)) this->explode(map, pos + dir * i, NORTH, range);
			if (!vecEqual(-dir, SOUTH)) this->explode(map, pos + dir * i, SOUTH, range);
			return;
		}
		if (tile == Tile::Destructible || tile == Tile::Solid)
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

std::string Bombs::to_string()
{
	std::ostringstream sstream;

	sstream << this->_bombs.size() << " ";

	for (sBomb bomb : this->_bombs)
	{
		sstream << bomb.position.x << " " << bomb.position.y << " " << bomb.timeLeft << " ";
	}
	sstream << '\n';

	sstream << this->_flames.size() << " ";

	for (sFlame flame : this->_flames)
	{
		sstream << flame.position.x << " " << flame.position.y << " " << flame.timeLeft << " ";
	}
	sstream << '\n';

	return sstream.str();
}

void Bombs::from_string(std::istream &istream)
{
	int n;
	istream >> n;

	this->_bombs.clear();
	this->_flames.clear();

	for (int i = 0; i < n; i++)
	{
		sBomb bomb;
		istream >> bomb.position.x >> bomb.position.y >> bomb.timeLeft;
		this->_bombs.push_back(bomb);
	}

	istream >> n;

	for (int i = 0; i < n; i++)
	{
		sFlame flame;
		istream >> flame.position.x >> flame.position.y >> flame.timeLeft;
		this->_flames.push_back(flame);
	}
}
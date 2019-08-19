#include "../include/Bombs.hpp"

const float FUSE_TIME = 2;

Bombs::Bombs()
	: _bombs()
{
}

void Bombs::placeBomb(const Player &player, Map &map)
{
	sf::Vector2i playerCell(player.position());

	if (map.tileAt(playerCell) == Tile::Clear)
	{
		map.setTile(playerCell, Tile::Bomb);

		sBomb newBomb;
		newBomb.position = playerCell;
		newBomb.timeLeft = FUSE_TIME;

		this->_bombs.push_back(newBomb);
	}
}

void Bombs::update(float deltaTime, Map &map)
{
	for (sBomb &bomb : this->_bombs)
	{
		bomb.timeLeft -= deltaTime;
		if (bomb.timeLeft < 0)
		{
			// Explode logic here
			map.setTile(bomb.position, Tile::Clear);
		}
	}
	this->_bombs.remove_if([](sBomb &bomb) { return bomb.timeLeft < 0; });
}

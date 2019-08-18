#include "../include/Bombs.hpp"

const float FUSE_TIME = 2;

void Bombs::placeBomb(const Player &player, Map &map)
{
	sf::Vector2i playerCell(player.position());

	if (map.tileAt(playerCell) == Tile::Clear)
	{
		map.setTile(playerCell, Tile::Bomb);

		sBomb newBomb;
		newBomb.position = playerCell;
		newBomb.timeLeft = FUSE_TIME;

		// this->_bombs.push_back(newBomb);
	}
}

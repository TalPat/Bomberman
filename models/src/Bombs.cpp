#include "../include/Bombs.hpp"

const float FUSE_TIME = 2;
const float FLAME_TIME = 0.2;

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

const float BOMB_RANGE = 1; // TODO: change based on player powerups
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
            for (int i = 1; i < BOMB_RANGE + 1; ++i)
            {
                this->placeFlame(bomb.position + sf::Vector2i(+i, 0), map);
                this->placeFlame(bomb.position + sf::Vector2i(-i, 0), map);
                this->placeFlame(bomb.position + sf::Vector2i(0, -i), map);
                this->placeFlame(bomb.position + sf::Vector2i(0, +i), map);
            }
            this->placeFlame(bomb.position, map);
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
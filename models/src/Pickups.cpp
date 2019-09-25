#include "../include/Pickups.hpp"
#include "../include/GameState.hpp"

#include <iostream>

Pickups::Pickups() {}

void Pickups::init(Map &map, int level)
{
	//Should change based on level being loaded
	
	this->_pickups.erase(this->_pickups.begin(),this->_pickups.end());

	sf::Vector2i size = map.size();
	std::vector<sf::Vector2i> availableCells;

	for (int y = 0; y < size.y; y++)
	{
		for (int x = 0; x < size.x; x++)
		{
			if (map.tileAt(sf::Vector2i(x, y)) == Tile::Destructible)
			{
				availableCells.push_back(sf::Vector2i(x, y));
			}
		}
	}
	auto rng = std::default_random_engine {};
	std::shuffle ( availableCells.begin(), availableCells.end(), rng );
	this->addPickup(availableCells.back(), PickupType::LevelUp);
	availableCells.pop_back();
	this->addPickup(availableCells.back(), PickupType::BombTotal);
	availableCells.pop_back();
	this->addPickup(availableCells.back(), PickupType::BombRange);
	availableCells.pop_back();
}

void Pickups::addPickup(sf::Vector2i pos, PickupType type)
{
	sPickup newPickup;
	newPickup.position = pos;
	newPickup.type = type;
	this->_pickups.push_back(newPickup);
}

void Pickups::update(GameState &state)
{
	std::list<sPickup>::iterator pickup = this->_pickups.begin();
	while (pickup != this->_pickups.end())
	{
		sf::Vector2i ppos(state.player.position());
		if (ppos.x == pickup->position.x && ppos.y == pickup->position.y)
		{
			if (pickup->type == PickupType::LevelUp && state.enemies.list.size() == 0)
			{
				state.loading = true;
				state.level++;
				this->_pickups.erase(pickup++);
			}
			else if (pickup->type == PickupType::LevelUp && state.enemies.list.size() != 0)
			{
				pickup++;
			}
			else if (pickup->type == PickupType::BombTotal)
			{
				state.player.addMaxBombs();
				this->_pickups.erase(pickup++);
			}
			else if (pickup->type == PickupType::BombRange)
			{
				state.player.addBombRange();
				this->_pickups.erase(pickup++);
			}
			else
			{
				++pickup;
			}
		}
		else
		{
			++pickup;
		}
	}
}
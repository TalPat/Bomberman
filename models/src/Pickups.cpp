#include "../include/Pickups.hpp"

Pickups::Pickups() {}

void Pickups::initPickups(Map &map)
{
	//Should change based on level being loaded
	
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

void Pickups::update(Player &player, Map &map)
{
	std::list<sPickup>::iterator i = this->_pickups.begin();
	while (i != this->_pickups.end())
	{
		sf::Vector2i ppos(player.position());
		if (ppos.x == i->position.x && ppos.y == i->position.y)
	    {
	        this->_pickups.erase(i++);
	    }
	    else
	    {
	    	++i;
	    }
	}
}
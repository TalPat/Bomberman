#ifndef PICKUPS_HPP
#define PICKUPS_HPP

#include "Map.hpp"
#include "Player.hpp"

#include <list>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

enum PickupType
{
	LevelUp,
	BombTotal,
	BombRange,
};

struct sPickup
{
	sf::Vector2i position;
	PickupType type;
};

class Pickups
{
private:
public:
	std::list<sPickup> _pickups;
	Pickups();
	void initPickups(Map &map);
	void addPickup(sf::Vector2i pos, PickupType type);
	void update(Player &player, Map &map);
};

#endif

#ifndef PICKUPS_HPP
#define PICKUPS_HPP

#include "Map.hpp"
#include "Player.hpp"
#include "Bombs.hpp"
#include "Enemies.hpp"

#include <algorithm>
#include <random>
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

class GameState;

class Pickups
{
private:
public:
	std::list<sPickup> _pickups;
	Pickups();
	void init(Map &map, int level);
	void addPickup(sf::Vector2i pos, PickupType type);
	void update(GameState &state);

	std::string to_string();
	void from_string(std::istream &istream);
};

#endif

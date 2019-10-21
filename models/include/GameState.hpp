#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "EngineEvent.hpp"
#include "Player.hpp"
#include "Enemies.hpp"
#include "Ballom.hpp"
#include "Map.hpp"
#include "Bombs.hpp"
#include "Pickups.hpp"

#include <SFML/System.hpp>
#include <iostream>
#include <vector>

class GameState
{
public:
	Player player;
	Enemies enemies;
	Map map;
	Bombs bombs;
	Pickups pickups;
	int level;
	bool loading;
	float waitTime;
};

#endif

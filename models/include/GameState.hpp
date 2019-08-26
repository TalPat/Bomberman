#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "./EngineEvent.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Map.hpp"
#include "Bombs.hpp"

#include <SFML/System.hpp>
#include <iostream>
#include <vector>

class GameState
{
public:
	Player player;

	Enemy enemy;
	Map map;
	Bombs bombs;
};

#endif

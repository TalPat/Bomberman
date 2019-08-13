#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "./EngineEvent.hpp"

#include <SFML/System.hpp>
#include <iostream>
#include <vector>

enum Tile
{
	Border,
	Solid,
	Clear,
	Destructible,
};

class GameState
{
public:
	GameState(int width, int height);
	~GameState();

	// Player
	sf::Vector2f playerPos;

	// Map
	int width;
	int height;
	std::vector<Tile> map;

	// int getTile(int x_coord, int y_coord) {
	// 	return this->walls[y_coord * width + x_coord];
	// }

	// void setTile(int x_coord, int y_coord, int val) {
	// 	this->walls[y_coord * width + x_coord] = val;
	// }
};

#endif

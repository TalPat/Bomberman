
#include "../include/Engine.hpp"

#include <iostream>
#include <vector>

void Engine::update(double deltaTime, std::vector<EngineEvent> &action, GameState &gameState))
{
	std::cout << "Updating Engine" << std::endl;
}

void Engine::movePlayer(EngineEvent event, float dd) {
	if (event == EngineEvent::move_left && !getTile(pos.y + 0.5, pos.x + 0.2 - dd))
		pos.x -= dd;
	if (event == EngineEvent::move_right && !getTile(pos.y + 0.5, pos.x + 0.8 + dd))
		pos.x += dd;
	if (event == EngineEvent::move_up && !getTile(pos.y + 0.2 - dd, pos.x + 0.5))
		pos.y -= dd;
	if (event == EngineEvent::move_down] && !getTile(pos.y + 0.8 + dd, pos.x + 0.5))
		pos.y += dd;
}

// Bombs
void Engine::tickBombs(float deltaTime)
{
	std::list<Bomb>::iterator i = bombs.begin();
	while (i != bombs.end())
	{
		(*i).tick += dt; // update bomb tick with game deltatime
		// When bomb reaches end of life, remove walls, remove bomb from bomb list
		if ((*i).tick > 2.6) {
			explodeBomb((*i).x, (*i).y, 1);
			// last parameter here is size ^^
			// should be changed based in powerup or something later
			bombs.erase(i++);
		}
		else
			i++;
	}
}

void GameState::placeBomb() {
	// place bomb at current player position
	Bomb new_bomb = {
		.x = (int)(pos.x+0.5),
		.y = (int)(pos.y+0.5),
		.tick = 0
	};
	bombs.push_back(new_bomb);
}

void explodeBomb(float x, float y, int size) {
	for (int i = 0; i < size; ++i)
	{
		if (getTile( y + i, x ) == 2) setTile( y + i, x, 0);
		if (getTile( y - i, x ) == 2) setTile( y - i, x, 0);
		if (getTile( y, x - i ) == 2) setTile( y, x - i, 0);
		if (getTile( y, x + i ) == 2) setTile( y, x + i, 0);
	}
}

int getTile(int x_coord, int y_coord) {
	return this->walls[y_coord * width + x_coord];
}
void setTile(int x_coord, int y_coord, int val) {
	this->walls[y_coord * width + x_coord] = val;
}


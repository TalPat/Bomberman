
#include "../include/Engine.hpp"

#include <iostream>
#include <vector>

void Engine::update(double deltaTime, std::vector<EngineEvent> &actions, GameState &gameState)
{
	MoveState &moveState = gameState.player.moveState;

	for (EngineEvent event : actions)
	{
		switch (event)
		{
		case EngineEvent::move_up:
			moveState.north = true;
			break;
		case EngineEvent::stop_up:
			moveState.north = false;
			break;
		case EngineEvent::move_right:
			moveState.east = true;
			break;
		case EngineEvent::stop_right:
			moveState.east = false;
			break;
		case EngineEvent::move_down:
			moveState.south = true;
			break;
		case EngineEvent::stop_down:
			moveState.south = false;
			break;
		case EngineEvent::move_left:
			moveState.west = true;
			break;
		case EngineEvent::stop_left:
			moveState.west = false;
			break;
		case EngineEvent::place_bomb:
			gameState.bombs.addBomb(gameState.player.position());
			break;
		default:
			break;
		}
	}

	gameState.bombs.update(deltaTime, gameState.map);

	gameState.player.move(deltaTime, gameState.map);
}

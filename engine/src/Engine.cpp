
#include "../include/Engine.hpp"

void Engine::init(GameState &gameState)
{
	//if (gameState.level != 0 && gameState.level % 5 == 0)
	//	gameState.player.addLife();
	gameState.loading = true;
	gameState.map.init(gameState.level);
	gameState.bombs.clear();
	gameState.enemies.init(gameState.level);
	gameState.player.init(gameState.level);
	gameState.pickups.init(gameState.map, gameState.level);
	gameState.loading = false;
}

void Engine::update(double deltaTime, std::vector<EngineEvent> &actions, GameState &gameState)
{
	if (gameState.loading)
	{
		this->init(gameState);
		return;
	}

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
			gameState.bombs.placeBomb(gameState.player, gameState.map);
		default:
			break;
		}
	}

	if (gameState.player.isAlive())
	{
		gameState.bombs.update(deltaTime, gameState.map);
		gameState.bombs.updateMap(gameState.player, gameState.map);
		gameState.pickups.update(gameState);
		gameState.enemies.updateAll(deltaTime, gameState.map);
		gameState.enemies.kill(gameState.map);
	}
	gameState.player.update(deltaTime, gameState.map);
	
}

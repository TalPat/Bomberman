#ifndef _ENGINE_HPP
#define _ENGINE_HPP

#include "./EngineEvent.hpp"

#include <GameState.hpp>

#include <vector>

class Engine
{
public:
	void update(double deltaTime, std::vector<EngineEvent> &actions, GameState &gameState);

	// void movePlayer(EngineEvent event, float dd);
	// void tickBombs(float deltaTime);
};

#endif

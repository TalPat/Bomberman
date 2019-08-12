#ifndef _ENGINE_HPP
#define _ENGINE_HPP

#include "./EngineEvent.hpp"
#include "GameState.hpp"

#include <vector>

class Engine
{
public:
	// deltaTime should be expressed in seconds
	// action might need to be vector as multiple keys can be pressed
	// in a single frame
	void update(double deltaTime, std::vector<EngineEvent> &actions);

	void movePlayer(EngineEvent event, float dd);
	void tickBombs(float deltaTime);
};

#endif

#ifndef _ENGINE_HPP
#define _ENGINE_HPP

#include "./EngineEvent.hpp"
#include "./GameState.hpp"

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

class Engine
{
private:
    bool *keys; // tracks whether a key is being held
public:
    void key_pressed(EngineEvent event, GameState &state, double dt);
    void key_released(EngineEvent event, GameState &state, double dt);
    void tickGame(double dt, GameState &state);
	void update(double dt, GameState &state);
    void loadLevel(GameState &game, int level);
    Engine();
    ~Engine();
};

#endif

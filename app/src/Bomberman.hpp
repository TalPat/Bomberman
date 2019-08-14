#ifndef _Bomberman_hpp_
#define _Bomberman_hpp_

#include "./AMainLoop.hpp"
#include "./Input.hpp"

#include <Engine.hpp>
#include <EngineEvent.hpp>
#include <Renderer.hpp>
#include <SFML/Graphics.hpp>
#include <GameState.hpp>

#include <vector>
#include <ctime>

static const uint WINDOW_WIDTH = 800;
static const uint WINDOW_HEIGHT = 800;
static const char *WINDOW_TITLE = "Bomberman";

class Bomberman : private AMainLoop
{
private:
	sf::RenderWindow window;
	Engine engine;
	Renderer renderer;
	Input input;

	GameState gameState;

	sf::Clock deltaClock;
	sf::Clock frameClock;
	float renderTime;
	float engineTime;

	virtual void updateFunc();

public:
	Bomberman();
	~Bomberman();

	void startGame();
};

#endif

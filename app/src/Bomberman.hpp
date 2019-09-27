#ifndef _Bomberman_hpp_
#define _Bomberman_hpp_

#include "./AMainLoop.hpp"
#include "./Input.hpp"

#include <Engine.hpp>
#include <EngineEvent.hpp>
#include <Renderer.hpp>
#include <GameState.hpp>

#include <vector>
#include <ctime>
#if !__APPLE__
	#include <X11/Xlib.h>
#endif

static const uint WINDOW_WIDTH = 800;
static const uint WINDOW_HEIGHT = 800;
static const char *WINDOW_TITLE = "Bomberman";

class Bomberman : private AMainLoop
{
private:
	sf::RenderWindow *window;
	Engine engine;
	Renderer renderer;
	Input input;

	GameState gameState;

	sf::Clock deltaClock;
	sf::Clock frameClock;
	float renderTime;
	float engineTime;

	virtual void updateFunc();

	static void *threadFunction(void *arg); //thread stuff
	pthread_t myThread;
	pthread_mutex_t *lock;
	bool threadActive;

public:
	Bomberman();
	~Bomberman();
	void setMutex(pthread_mutex_t *mutex);

	void startGame();
};

#endif

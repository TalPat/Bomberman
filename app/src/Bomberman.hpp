#ifndef _Bomberman_hpp_
#define _Bomberman_hpp_

#include "./AMainLoop.hpp"
#include "./Input.hpp"
#include "./Menu.hpp"

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

enum MenuState
{
	MainMenu,
	PauseMenu,
	SettingsMenu,
	ResolutionMenu,
	ControlsMenu,
	Playing
};

class Bomberman : private AMainLoop
{
private:
	sf::RenderWindow *window;
	Engine engine;
	Renderer renderer;
	Input input;
	
	Menu mainMenu;
	Menu pauseMenu;
	Menu settingsMenu;
	Menu resolutionMenu;
	Menu controlsMenu;
	MenuState menuState;

	GameState gameState;

	sf::Clock deltaClock;
	sf::Clock frameClock;
	float renderTime;
	float engineTime;

	virtual void updateFunc();

	void handleMenuAction(MenuAction option);

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

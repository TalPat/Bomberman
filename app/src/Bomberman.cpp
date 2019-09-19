
#include "./Bomberman.hpp"

#include <stdexcept>
#include <iostream>
#include <pthread.h>

const int MAP_WIDTH = 11;
const int MAP_HEIGHT = 11;

Bomberman::Bomberman()
		: renderTime(0),
			engineTime(0)
{
	sf::ContextSettings settings;
	settings.depthBits = 32;
	settings.majorVersion = 3;
	settings.minorVersion = 3;
	settings.antialiasingLevel = 4;
	settings.attributeFlags = sf::ContextSettings::Core;

	window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Default, settings);
	window->setActive();
	renderer.init();

	std::vector<MenuItem> mainMenuItems;
	mainMenuItems.push_back(MenuItem(-2, "Start", true, MenuOption::Start));
	mainMenuItems.push_back(MenuItem(0, "Controls", false, MenuOption::Controls));
	mainMenuItems.push_back(MenuItem(2, "Exit", false, MenuOption::Exit));
	mainMenu.init(renderer, mainMenuItems);

	std::vector<MenuItem> pauseMenuItems;
	pauseMenuItems.push_back(MenuItem(-1, "Continue", true, MenuOption::Start));
	pauseMenuItems.push_back(MenuItem(1, "Main Menu", false, MenuOption::Exit));
	pauseMenu.init(renderer, pauseMenuItems);

	menuState = MenuState::MainMenu;

	this->deltaClock.restart();
	this->frameClock.restart();

	//thread stuff
	threadActive = false;
	this->engine.init(this->gameState);
}

Bomberman::~Bomberman()
{
}

void Bomberman::startGame()
{
	this->start();
}

void Bomberman::handleMenuOption(MenuOption option)
{
	switch (option)
	{
	case MenuOption::Start:
		this->menuState = MenuState::Playing;
		break;
	case MenuOption::Exit:
		this->stop();
		break;
	default:
		break;
	}
}


void *Bomberman::threadFunction(void *arg)
{
	Bomberman *bman = (Bomberman *)arg;

	// uncomment if object must be mutated by renderer
	// pthread_mutex_lock(bman->lock);

	bman->renderer.render(*(bman->window), bman->gameState);
	bman->threadActive = false;
	
	// uncomment if object must be mutated by renderer
	// pthread_mutex_unlock(bman->lock);
}

void Bomberman::updateFunc()
{
	if (!this->window->isOpen())
		this->stop();

	sf::Event event;
	std::vector<EngineEvent> actions;
	InputResponse response = this->input.parseKeys(actions, *window);
	switch (response)
	{
	case InputResponse::quit:	
		this->stop();
		break;
	case InputResponse::pause:
		// Can be used to pause game with 'Esc' key
		if (this->menuState == MenuState::PauseMenu)
			this->menuState = MenuState::Playing;
		else if (this->menuState == MenuState::Playing)
			this->menuState = MenuState::PauseMenu;
		break;
	default:
		break;
	}

	// Record the time elapsed since starting last render
	this->renderTime = this->deltaClock.getElapsedTime().asSeconds();
	this->deltaClock.restart();

	if (this->menuState == MenuState::Playing)
	{
		this->engine.update(this->renderTime + this->engineTime, actions, this->gameState);
	}
	// Record the time taken by the engine
	this->engineTime = this->deltaClock.getElapsedTime().asSeconds();
	this->deltaClock.restart();

	MenuOption option = MenuOption::Nothing;

	if (this->menuState == MenuState::Playing)
	{
		// Only render if required to enforce frameRate
		if (this->frameClock.getElapsedTime().asSeconds() >= this->perFrameSeconds)
		{
			if (!threadActive)
			{
				this->frameClock.restart();
				threadActive = true;
				pthread_create(&myThread, NULL, Bomberman::threadFunction, (void*)this);
			}
		}
	}
	else if (this->menuState == MenuState::MainMenu)
	{
		option = this->mainMenu.render(*(this->window), actions);
		this->handleMenuOption(option);
	}
	else if (this->menuState == MenuState::PauseMenu)
	{
		option = this->pauseMenu.render(*(this->window), actions);
		this->handleMenuOption(option);
	}
}

void Bomberman::setMutex(pthread_mutex_t *mutex) {
	lock = mutex;
}

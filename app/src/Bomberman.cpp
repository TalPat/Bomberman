
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

	this->deltaClock.restart();
	this->frameClock.restart();

	//thread stuff
	threadActive = false;
	this->gameState.level = 0;
	this->engine.init(this->gameState);
}

Bomberman::~Bomberman()
{
}

void Bomberman::startGame()
{
	this->saveGame();
	this->start();
};

// std::string path = SETTINGS_DIR + std::string("/input_map.cfg");
void Bomberman::saveGame()
{
	std::string path = SETTINGS_DIR + std::string("/gamestate.cfg");
	std::ofstream saveFile;
	saveFile.open(path);

	

	saveFile.close();
}

void Bomberman::loadGame()
{

}

void *Bomberman::threadFunction(void *arg)
{
	Bomberman *bman = (Bomberman *)arg;

	// uncomment if object must be mutated by renderer
	// pthread_mutex_lock(bman->lock);

	bman->renderer.render(*(bman->window), bman->gameState);
	bman->threadActive = false;
	return (NULL);
	// uncomment if object must be mutated by renderer
	// pthread_mutex_unlock(bman->lock);
}

void Bomberman::updateFunc()
{
	if (!this->window->isOpen())
		this->stop();

	sf::Event event;
	std::vector<EngineEvent> actions;
	input.parseKeys(actions, *window);

	// Record the time elapsed since starting last render
	this->renderTime = this->deltaClock.getElapsedTime().asSeconds();
	this->deltaClock.restart();

	this->engine.update(this->renderTime + this->engineTime, actions, this->gameState);

	// Record the time taken by the engine
	this->engineTime = this->deltaClock.getElapsedTime().asSeconds();
	this->deltaClock.restart();

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

void Bomberman::setMutex(pthread_mutex_t *mutex) {
	lock = mutex;
}

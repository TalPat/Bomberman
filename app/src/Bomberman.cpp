
#include "./Bomberman.hpp"

#include <stdexcept>
#include <iostream>

const int MAP_WIDTH = 11;
const int MAP_HEIGHT = 11;

Bomberman::Bomberman()
	: window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE),
	  renderTime(0),
	  engineTime(0)
{
	this->deltaClock.restart();
	this->frameClock.restart();
}

Bomberman::~Bomberman()
{
}

void Bomberman::startGame()
{
	this->start();
};

void Bomberman::updateFunc()
{
	if (!this->window.isOpen())
		this->stop();

	sf::Event event;
	std::vector<EngineEvent> actions;
	InputResponse response = this->input.parseKeys(actions, this->window);
	switch (response)
	{
	case InputResponse::quit:	
		this->stop();
		break;
	case InputResponse::pause:
		// Can be used to pause game with 'Esc' key
		this->stop();
		break;
	default:
		break;
	}

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
		this->renderer.render(this->window, this->gameState);
		this->frameClock.restart();
	}
}

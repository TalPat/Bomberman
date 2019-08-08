
#include "./Bomberman.hpp"

#include <stdexcept>
#include <iostream>

Bomberman::Bomberman()
	: window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE),
	  renderTime(0), engineTime(0)
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
	while (this->window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				this->stop();
				this->window.close();
				break;
			case sf::Event::KeyPressed:
				EngineEvent pressed = this->input.getInput(event.key.code);
				if (pressed != EngineEvent::unknown)
					actions.push_back(pressed);
				break;
		}
	}

	if (actions.size() == 0)
		actions.push_back(EngineEvent::stop);

	// Record the time elapsed since starting last render
	this->renderTime = this->deltaClock.getElapsedTime().asSeconds();
	this->deltaClock.restart();

	this->engine.update(this->renderTime + this->engineTime, actions);

	// Record the time taken by the engine
	this->engineTime = this->deltaClock.getElapsedTime().asSeconds();
	this->deltaClock.restart();

	// Only render if required to enforce frameRate
	if (this->frameClock.getElapsedTime().asSeconds() > this->perFrameSeconds)
	{
		this->renderer.render(this->window);
		this->frameClock.restart();
	}
}

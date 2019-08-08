
#include "./Bomberman.hpp"

#include <stdexcept>
#include <iostream>
#include <sys/time.h> 

Bomberman::Bomberman()
	: window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE)
{
}

Bomberman::~Bomberman()
{
}

long currentTimeMicro()
{
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);
    return (currentTime.tv_sec * (int)1e6 + currentTime.tv_usec) / 100;
}

void Bomberman::startGame()
{
	// init deltatime
	this->engine.now = currentTimeMicro();
	this->start();
};

void Bomberman::updateFunc()
{

	if (!this->window.isOpen())
		this->stop();

	sf::Event event;
	while (this->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			this->stop();
			window.close();
		}
	}

	this->engine.update();
	this->renderer.render(this->window, this->engine);
	
	// deltatime
	this->engine.dt = currentTimeMicro() - this->engine.now;
	this->engine.now = currentTimeMicro();

	// TODO: Need a class to map key to event
	// @Whoever wrote this, we can also use
	// sf::Keyboard::isKeyPressed(); instead of polling events, using event vectors etc..
	// Check might need to be done
}

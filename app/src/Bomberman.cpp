
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

double currentTimeMicro()
{
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);
    return (currentTime.tv_sec * (int)1e6 + currentTime.tv_usec) / 1000000.0;
}

void Bomberman::startGame()
{
	// init deltatime
	this->now = currentTimeMicro();
	this->start();
};

void Bomberman::updateFunc()
{

	if (!this->window.isOpen())
		this->stop();
	
	this->dt = currentTimeMicro() - this->now;
	this->now = currentTimeMicro();

	sf::Event event;
	while (this->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			this->stop();
			window.close();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			if (this->key_map.find(event.key.code) != this->key_map.end()) {
				this->engine.key_pressed( this->key_map[ event.key.code ], this->state, this->dt );
			}
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			if (this->key_map.find(event.key.code) != this->key_map.end()) {
				this->engine.key_released( this->key_map[ event.key.code ], this->state, this->dt );
			}
		}
	}

	//std::cout << this->dt << "\n";
	this->engine.update(this->dt, this->state);
	this->renderer.render(this->window, this->state);
	
	// deltatime
}

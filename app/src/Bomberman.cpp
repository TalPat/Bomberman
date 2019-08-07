
#include "./Bomberman.hpp"

#include <stdexcept>
#include <iostream>

Bomberman::Bomberman()
	: window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE)
{
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
	EngineEvent engEvent = EngineEvent::stop;
	while (this->window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				this->stop();
				this->window.close();
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code) {
					case sf::Keyboard::Escape:
						this->stop();
						this->window.close();
						break;
					case sf::Keyboard::Up:
						engEvent = EngineEvent::move_up;
						break;
					case sf::Keyboard::Down:
						engEvent = EngineEvent::move_down;
						break;
					case sf::Keyboard::Left:
						engEvent = EngineEvent::move_left;
						break;
					case sf::Keyboard::Right:
						engEvent = EngineEvent::move_right;
						break;
					case sf::Keyboard::Space:
						engEvent = EngineEvent::place_bomb;
						break;
				}
				break;
		}
	}

	double deltaTime;
	if (this->_sleep.tv_nsec > this->_perFrameTime.tv_nsec)
		deltaTime = static_cast<double>(this->_diff.tv_nsec) / 1000000000;
	else
		deltaTime = static_cast<double>(this->_perFrameTime.tv_nsec) / 1000000000;

	// TODO: Need a class to map key to event
	this->engine.update(deltaTime, engEvent);

	// Check might need to be done
	this->renderer.render(this->window);
}

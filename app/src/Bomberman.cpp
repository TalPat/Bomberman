
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

	double deltaTime;
	if (this->_sleep.tv_nsec > this->_perFrameTime.tv_nsec)
		deltaTime = static_cast<double>(this->_diff.tv_nsec) / 1000000000;
	else
		deltaTime = static_cast<double>(this->_perFrameTime.tv_nsec) / 1000000000;

	// TODO: Need a class to map key to event
	this->engine.update(deltaTime, actions);

	// Check might need to be done
	this->renderer.render(this->window);
}

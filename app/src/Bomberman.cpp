
#include "./Bomberman.hpp"

#include <stdexcept>
#include <iostream>

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
	menu.init(renderer);

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
		// this->renderer.render(*(this->window), this->gameState);
		this->menu.render(*(this->window), this->gameState);
		std::string textString = "FPS " + std::to_string((int)(1 / this->frameClock.getElapsedTime().asSeconds()));
		sf::Vector3i color = sf::Vector3i(10, 20, 50);
		sf::Vector2f startLocation = sf::Vector2f(-1.0f, -1.0f);
		float scale = 0.2f;
		// example of "writeline implementation, rather use in renderer to avoid syncopated draw calls
		renderer.writeLine(*window, textString, color, startLocation, scale);
		this->frameClock.restart();
	}
}

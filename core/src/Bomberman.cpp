
#include "./Bomberman.hpp"

Bomberman::Bomberman(){};
Bomberman::~Bomberman() {}

void Bomberman::startGame()
{
	this->start();
};

void Bomberman::updateFunc()
{
	this->engine.update();
	this->renderer.render();
}

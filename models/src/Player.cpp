#include "../include/Player.hpp"

#include <iostream>

Player::~Player()
{
}

void Player::render(sf::RenderWindow &ctx)
{
	std::cout << "Rending Player" << std::endl;
}

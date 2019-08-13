#include "../include/Player.hpp"

#include <iostream>

const sf::Vector2f DEFAULT_START(0.5, 0.5);
const float DEFAULT_SPEED = 10;

Player::Player()
	: _position(DEFAULT_START),
	  _playerSpeed(DEFAULT_SPEED)
{
}

Player::~Player()
{
}

void Player::move(float deltaTime)
{
	MoveState &moveState = this->moveState;

	sf::Vector2f movement(0, 0);
	movement.x += moveState.east;
	movement.x -= moveState.west;
	movement.y += moveState.north;
	movement.y -= moveState.south;

	// std::cout << "Movement: " << (movement).x << ", " << (movement).y << std::endl;
	// std::cout << "Delta time: " << deltaTime << std::endl;

	// std::cout << (movement * this->_playerSpeed * deltaTime).x << ", " << (movement * this->_playerSpeed * deltaTime).y << std::endl;
	this->_position = this->_position + (movement * this->_playerSpeed * deltaTime);
}

const sf::Vector2f &Player::position() const
{
	return this->_position;
};

#include "../include/Player.hpp"

#include <iostream>
#include <cmath>

const sf::Vector2f DEFAULT_START(1.5, 1.5);
const float DEFAULT_SPEED = 3;

Player::Player() : _position(DEFAULT_START),
				   _playerSpeed(DEFAULT_SPEED),
				   moveState({false, false, false, false})
{
}

Player::~Player()
{
}

void Player::move(float deltaTime, const Map &map)
{
	MoveState &moveState = this->moveState;

	sf::Vector2f movement(0, 0);
	movement.x += moveState.east;
	movement.x -= moveState.west;
	movement.y -= moveState.north;
	movement.y += moveState.south;

	movement *= this->_playerSpeed * deltaTime;

	if (movement.x != 0 && movement.y != 0)
	{
		for (float i = 1.0; i > 0.04; i *= 0.5)
		{
			sf::Vector2f newPos = this->_position + (i * movement);
			if (!map.collide(newPos, 0.45)) {
				this->_position = newPos;
				return;
			}
		}
	}
	if (movement.x != 0)
	{
		for (float i = 1.0; i > 0.04; i *= 0.5)
		{
			sf::Vector2f newPosX = this->_position + (i * sf::Vector2f(movement.x, 0));
			if (!map.collide(newPosX, 0.45)) {
				this->_position = newPosX;
				return;
			}
		}
	}
	if (movement.y != 0)
	{
		for (float i = 1.0; i > 0.04; i *= 0.5)
		{
			sf::Vector2f newPosY = this->_position + (i * sf::Vector2f(0, movement.y));
			if (!map.collide(newPosY, 0.45)) {
				this->_position = newPosY;
				return;
			}
		}
	}
}

const sf::Vector2f &Player::position() const
{
	return this->_position;
};

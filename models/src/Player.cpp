#include "../include/Player.hpp"

#include <iostream>
#include <cmath>

const sf::Vector2f DEFAULT_START(1.5, 1.5);
const float DEFAULT_SPEED = 5;

// Testing order here is important
// Test cardinals first
const sf::Vector2i TEST_NEIGHBOURS[8] = {
	sf::Vector2i(0, 1),   //NORTH
	sf::Vector2i(1, 0),   //EAST
	sf::Vector2i(0, -1),  //SOUTH
	sf::Vector2i(-1, 0),  //WEST
	sf::Vector2i(1, 1),   //NE
	sf::Vector2i(-1, 1),  //SE
	sf::Vector2i(1, -1),  //SW
	sf::Vector2i(-1, -1), //NW
};

Player::Player() : _position(DEFAULT_START),
				   _playerSpeed(DEFAULT_SPEED)
{
}

Player::~Player()
{
}

bool Player::correctPlayerCellCollision(sf::Vector2i cell)
{
	const float RADIUS = 0.5;

	// Use variables to avoid multiple pointer refs
	float playerX = this->_position.x;
	float playerY = this->_position.y;
	int cellX = cell.x;
	int cellY = cell.y;

	float testX = playerX;
	float testY = playerY;

	// Check for the closest edge
	if (playerX < cellX)
		testX = cellX; // Left edge
	else if (playerX > cellX + 1)
		testX = cellX + 1; // Right edge
	if (playerY < cellY)
		testY = cellY; // Top edge
	else if (playerY > cellY + 1)
		testY = cellY + 1; // Bottom edge

	// Evaluate distance from closest edges
	sf::Vector2f diff(playerX - testX, playerY - testY);

	// Pythag distance needed for corners
	float distance = std::sqrt((diff.x * diff.x) + (diff.y * diff.y));

	// If the distance is less than the radius, collision!
	if (distance <= RADIUS - 0.0001)
	{
		if (diff.y == 0)
		{
			if (playerX > cellX)
				this->_position.x += RADIUS - diff.x;
			else
				this->_position.x -= RADIUS + diff.x;
		}
		else if (diff.x == 0)
		{
			if (playerY > cellY)
				this->_position.y += RADIUS - diff.y;
			else
				this->_position.y -= RADIUS + diff.y;
		}
		else
		{
			sf::Vector2f corner(testX, testY);
			sf::Vector2f correction = (diff / distance) * RADIUS;
			this->_position = corner + correction;
		}
		return true;
	}
	return false;
}

void Player::move(float deltaTime, const Map &map)
{
	MoveState &moveState = this->moveState;

	sf::Vector2f movement(0, 0);
	movement.x += moveState.east;
	movement.x -= moveState.west;
	movement.y -= moveState.north;
	movement.y += moveState.south;

	this->_position = this->_position + (movement * this->_playerSpeed * deltaTime);
	sf::Vector2i playerCell(this->_position);

	for (sf::Vector2i direction : TEST_NEIGHBOURS)
	{
		sf::Vector2i cell = playerCell + direction;
		if (map.tileAt(cell) != Tile::Clear)
		{
			if (correctPlayerCellCollision(cell))
				break;
		}
	}
}

const sf::Vector2f &Player::position() const
{
	return this->_position;
};

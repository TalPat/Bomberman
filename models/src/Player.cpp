#include "../include/Player.hpp"

#include <iostream>
#include <cmath>

const sf::Vector2f DEFAULT_START(1.5, 1.5);
const float DEFAULT_SPEED = 5;

const sf::Vector2i TEST_CARDINALS[4] = {
	sf::Vector2i(0, 1),  //NORTH
	sf::Vector2i(1, 0),  //EAST
	sf::Vector2i(0, -1), //SOUTH
	sf::Vector2i(-1, 0), //WEST
};

const sf::Vector2i TEST_DIAG[4] = {
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

bool Player::correctPlayerCellCollisionDiag(sf::Vector2i cell)
{
	// Use variables to avoid pointer refs
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
	float distX = playerX - testX;
	float distY = playerY - testY;
	// Pythag distance needed for corners
	float distance = std::sqrt((distX * distX) + (distY * distY));

	// If the distance is less than the radius, collision!
	const float RADIUS = 0.4999;
	if (distance <= RADIUS)
	{
		sf::Vector2f corner(testX, testY);
		sf::Vector2f dist(distX, distY);
		dist /= distance;
		dist *= RADIUS;
		this->_position = corner + dist;
	}
	return false;
}

bool Player::correctPlayerCellCollision(sf::Vector2i cell)
{
	// Use variables to avoid pointer refs
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
	float distX = playerX - testX;
	float distY = playerY - testY;
	// Pythag distance needed for corners
	float distance = std::sqrt((distX * distX) + (distY * distY));

	// If the distance is less than the radius, collision!
	const float RADIUS = 0.4999;
	if (distance <= RADIUS)
	{
		if (distX != 0)
		{
			if (playerX > cellX)
				this->_position.x += RADIUS - distX;
			else
				this->_position.x -= RADIUS + distX;
		}
		else if (distY != 0)
		{
			if (playerY > cellY)
				this->_position.y += RADIUS - distY;
			else
				this->_position.y -= RADIUS + distY;
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

	// Because its a cell based game. And the "Size" of the player
	// We only need to check on the cardinals
	for (sf::Vector2i direction : TEST_CARDINALS)
	{
		sf::Vector2i cell = playerCell + direction;
		if (map.tileAt(cell) != Tile::Clear)
		{
			if (correctPlayerCellCollision(cell))
				break;
		}
	}

	for (sf::Vector2i direction : TEST_DIAG)
	{
		sf::Vector2i cell = playerCell + direction;
		if (map.tileAt(cell) != Tile::Clear)
		{
			if (correctPlayerCellCollisionDiag(cell))
				break;
		}
	}
}

const sf::Vector2f &Player::position() const
{
	return this->_position;
};

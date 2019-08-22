#include "../include/Enemy.hpp"

#include <iostream>
#include <cmath>

const float AUTOSWITCH = 8;
const sf::Vector2f DEFAULT_START(11.5, 11.5);
const float DEFAULT_SPEED = 3.5;
const int NUM_STATES = 4;

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

Enemy::Enemy() : _position(DEFAULT_START),
				   _enemySpeed(DEFAULT_SPEED),
				   moveState(EnemyMoveState::north),
				   _switchTime(AUTOSWITCH),
				   appears({1,2})
{
}

Enemy::~Enemy()
{
}

bool Enemy::correctEnemyCellCollision(sf::Vector2i cell)
{
	const float RADIUS = 0.5;

	// Use variables to avoid multiple pointer refs
	float enemyX = this->_position.x;
	float enemyY = this->_position.y;
	int cellX = cell.x;
	int cellY = cell.y;

	float testX = enemyX;
	float testY = enemyY;

	// Check for the closest edge
	if (enemyX < cellX)
		testX = cellX; // Left edge
	else if (enemyX > cellX + 1)
		testX = cellX + 1; // Right edge
	if (enemyY < cellY)
		testY = cellY; // Top edge
	else if (enemyY > cellY + 1)
		testY = cellY + 1; // Bottom edge

	// Evaluate distance from closest edges
	sf::Vector2f diff(enemyX - testX, enemyY - testY);

	// Pythag distance needed for corners
	float distance = std::sqrt((diff.x * diff.x) + (diff.y * diff.y));

	// If the distance is less than the radius, collision!
	if (distance <= RADIUS - 0.0001)
	{
		if (diff.y == 0)
		{
			if (enemyX > cellX)
				this->_position.x += RADIUS - diff.x;
			else
				this->_position.x -= RADIUS + diff.x;
		}
		else if (diff.x == 0)
		{
			if (enemyY > cellY)
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
		changeMoveState();
		return true;
	}
	return false;
}

void Enemy::changeMoveState(){
	// int max = 3;
	// int min = 0;
	int num;
	num = (rand() % (NUM_STATES));
	moveState = num;
	// switch(num){
	// 	case EnemyMoveState::north:
	// 		moveState = EnemyMoveState::north;
	// 		// moveState.south = false;
	// 		// moveState.east = false;
	// 		// moveState.west = false;
	// 		break;
	// 	case  EnemyMoveState::south:
	// 		moveState = EnemyMoveState::south;
	// 		// moveState.south = true;
	// 		// moveState.north = false;
	// 		// moveState.east = false;
	// 		// moveState.west = false;
	// 		break;
	// 	case  EnemyMoveState::east:
	// 		moveState = EnemyMoveState::east;
	// 		// moveState.east = true;
	// 		// moveState.west = false;
	// 		// moveState.north = false;
	// 		// moveState.south = false;
	// 		break;
	// 	case  EnemyMoveState::west:
	// 		moveState = EnemyMoveState::west;
	// 		// moveState.west = true;
	// 		// moveState.east = false;
	// 		// moveState.north = false;
	// 		// moveState.south = false;
	// 		break;
	// 	default:
	// 		moveState = EnemyMoveState::west;
	// 		// moveState.north = false;
	// 		// moveState.south = false;
	// 		// moveState.east = false;
	// 		// moveState.west = false;
	// 		break;
	// }
}
void Enemy::update(float deltaTime, const Map &map){
	_switchTime -= deltaTime;
	if(_switchTime <= 0){
		changeMoveState();
		_switchTime = AUTOSWITCH;
	}
	move(deltaTime, map);
}
void Enemy::move(float deltaTime, const Map &map)
{
	int moveState = this->moveState;
	sf::Vector2f movement(0, 0);
	if(moveState == EnemyMoveState::east)
		movement.x += 1;
	if(moveState == EnemyMoveState::west)
		movement.x -= 1;
	if(moveState == EnemyMoveState::north)
		movement.y -= 1;
	if(moveState == EnemyMoveState::south)
		movement.y += 1;
	
	this->_position = this->_position + (movement * this->_enemySpeed * deltaTime);
	sf::Vector2i enemyCell(this->_position);

	for (sf::Vector2i direction : TEST_NEIGHBOURS)
	{
		sf::Vector2i cell = enemyCell + direction;
		Tile tile = map.tileAt(cell);
		if (!(tile == Tile::Clear /*|| tile == Tile::Bomb*/))
		{
			if (correctEnemyCellCollision(cell)){
				break;
			}
		}
	}
}

const sf::Vector2f &Enemy::position() const
{
	return this->_position;
};

#include "../include/Enemy.hpp"

#include <iostream>
#include <cmath>

const float AUTOSWITCH = 2;
const sf::Vector2f DEFAULT_START(11.5, 11.5);
const float DEFAULT_SPEED = 2.5;

Enemy::Enemy() : _position(DEFAULT_START),
				   _enemySpeed(DEFAULT_SPEED),
				   moveState({1, false, false, false}),
				   _switchTime(AUTOSWITCH)
{
}

Enemy::~Enemy()
{
}

void Enemy::changeMoveState(){

}

void Enemy::update(float deltaTime, const Map &map){
	_switchTime -= deltaTime;
	if(_switchTime <= 0)
	{
		changeMoveState();
	}
	move(deltaTime, map);
}
void Enemy::move(float deltaTime, const Map &map)
{
	EnemyMoveState &moveState = this->moveState;

	sf::Vector2f movement(0, 0);
	movement.x = moveState.east - moveState.west;
	movement.y = moveState.south - moveState.north;
	
	movement *= this->_enemySpeed * deltaTime;

	sf::Vector2f &pos = this->_position;

	auto comp = [](Tile tile) {
		return tile != Tile::Clear;
	};
	// if collided, turn around
	if (!map.lerpCollide(pos, movement, 0.49, comp))
	{
		if (moveState.north)
		{
			this->moveState.north = false;
			this->moveState.south = true;
		}
		else if (moveState.south)
		{
			this->moveState.south = false;
			this->moveState.north = true;
		}
		else if (moveState.east)
		{
			this->moveState.east = false;
			this->moveState.west = true;
		}
		else if (moveState.west)
		{
			this->moveState.west = false;
			this->moveState.east = true;
		}
	}

	// TODO: will merge later with gabie
	if(_switchTime < 0){
		sf::Vector2i cell(this->_position.x, this->_position.y);
		float xp = this->_position.x;
		float yp = this->_position.y;
		if (xp >= cell.x+0.49 && xp <= cell.x+0.51 &&
			yp >= cell.y+0.49 && yp <= cell.y+0.51)
		{
			if (moveState.north || moveState.south)
			{
				if (rand() % 2 && map.tileAt(sf::Vector2i(cell.x + 1, cell.y)) == Tile::Clear)
				{
					this->moveState = {false, true, false, false};
					_switchTime = AUTOSWITCH;
				}
				else if (map.tileAt(sf::Vector2i(cell.x - 1, cell.y)) == Tile::Clear)
				{
					this->moveState = {false, false, false, true};
					_switchTime = AUTOSWITCH;
				} 
			}
			if (moveState.east || moveState.west)
			{
				if (rand() % 2 && map.tileAt(sf::Vector2i(cell.x, cell.y + 1)) == Tile::Clear)
				{
					this->moveState = {false, false, true, false};
					_switchTime = AUTOSWITCH;
				}
				else if (map.tileAt(sf::Vector2i(cell.x, cell.y - 1)) == Tile::Clear)
				{
					this->moveState = {true, false, false, false};
					_switchTime = AUTOSWITCH;
				} 
			}
		}
	}
}

const sf::Vector2f &Enemy::position() const
{
	return this->_position;
};

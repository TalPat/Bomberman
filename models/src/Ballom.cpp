#include "../include/Ballom.hpp"
#include <RNG.hpp>

const int NUM_MOVEMENT_STATES = 4;
const float AGGROTIME = 4;
const float DEFAULT_SPEED = 2.5;
const float AUTOSWITCH = 8;
const sf::Vector2f DEFAULT_START(9.5, 9.5);

Ballom::Ballom()		
{
	_position = (DEFAULT_START);
	_enemySpeed = (DEFAULT_SPEED);
	moveState = (EnemyMoveState::north);
	_switchTime = (AUTOSWITCH);
	type = (EnemyType::EBallom);
	_wallPass = (true);
	changeMoveState();
}

Ballom::Ballom(sf::Vector2f start)		
{
	_position = (start);
	_enemySpeed = (DEFAULT_SPEED);
	moveState = (EnemyMoveState::north);
	_switchTime = (AUTOSWITCH);
	type = (EnemyType::EBallom);
	_wallPass = (true);
	changeMoveState();
}

Ballom::~Ballom(){
	return;
}

void Ballom::changeMoveState()
{
	int num = RNG::getRandomNumber(0, NUM_MOVEMENT_STATES - 1);
	this->moveState =(EnemyMoveState)(num);
}

void Ballom::update(float deltaTime, const Map &map, const Player &player)
{
	_switchTime -= deltaTime;
	_aggression -= deltaTime;
	if(_aggression <= 0)
	{
		this->changeAggression();
	}
	if(_switchTime <= 0)
	{
		this->changeMoveState();
		if(_aggression)
			_switchTime = (RNG::getRandomNumber(0, (int)(AUTOSWITCH/2))) + 1;
		else
			_switchTime = (RNG::getRandomNumber(0, (int)(AUTOSWITCH))) + 1;
	}
	this->move(deltaTime, map);
}

void Ballom::changeAggression()
{
	_aggression = (RNG::getRandomNumber (0, 3));
	if(_aggression == 3 && type == EnemyType::EBallom)
	{
		_enemySpeed = DEFAULT_SPEED + 1.5;
		type = EnemyType::EAggroBallom;
	}
	else
	{
		_enemySpeed = DEFAULT_SPEED;
		type = EnemyType::EBallom;
	}
		_aggression = AGGROTIME;		
}
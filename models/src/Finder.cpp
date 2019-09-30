#include "../include/Finder.hpp"
#include <RNG.hpp>

const int NUM_MOVEMENT_STATES = 4;
const float AGGROTIME = 4;
const float DEFAULT_SPEED = 2.5;
const float AUTOSWITCH = 1;
const bool DEFAULT_WALLPASS = true;
const int SIGHT_RANGE = 8;
const sf::Vector2f DEFAULT_START(9.5, 9.5);

Finder::Finder()
{
	_position = (DEFAULT_START);
	_enemySpeed = (DEFAULT_SPEED);
	moveState = (EnemyMoveState::north);
	_switchTime = (AUTOSWITCH);
	type = (EnemyType::EFinder);
	_wallPass = (DEFAULT_WALLPASS);
	changeMoveState();
}

Finder::Finder(sf::Vector2f start)
{
	_position = (start);
	_enemySpeed = (DEFAULT_SPEED);
	moveState = (EnemyMoveState::north);
	_switchTime = (AUTOSWITCH);
	type = (EnemyType::EFinder);
	_wallPass = (DEFAULT_WALLPASS);
	changeMoveState();
}

Finder::~Finder()
{
	return;
}

void Finder::changeMoveState()
{
	this->moveState =(EnemyMoveState)(RNG::getRandomNumber(0, NUM_MOVEMENT_STATES - 1));
}

void Finder::changeMoveState(const Map &map, const Player &player)
{
	this->moveState = findpath(map, sf::Vector2i(this->position()), sf::Vector2i(player.position()));
}

void Finder::update(float deltaTime, const Map &map, const Player &player)
{
	_switchTime -= deltaTime;
	double mf, xdec, ydec;
	xdec = modf(this->position().x, &mf);
	ydec = modf(this->position().y, &mf);
	sf::Vector2i dist = distance(sf::Vector2i(this->position()), sf::Vector2i(player.position()));
	if(abs(dist.y) < SIGHT_RANGE && abs(dist.x) < SIGHT_RANGE){
		if((xdec <0.55 && xdec > 0.4) && (ydec <0.55 && ydec > 0.4) && ((int)(this->position().x) % 2 || (int)(this->position().y) % 2))
			this->changeMoveState(map, player);
	}else{
		if(_switchTime <= 0)
		{	
			this->changeMoveState();
			_switchTime = (RNG::getRandomNumber(0, (int)(AUTOSWITCH))) + 1;
		}
	}
	this->move(deltaTime, map);
}

void Finder::changeAggression()
{
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

sf::Vector2i Finder::distance(sf::Vector2i start, sf::Vector2i end)
{
	int dy = start.y - end.y;
	int dx = start.x - end.x;
	return (sf::Vector2i(dx, dy));
}

EnemyMoveState Finder::calculatedirection(sf::Vector2i start, sf::Vector2i end)
{
	sf::Vector2i dist = distance(start, end);
	if(start.x % 2 == 0)
		dist.y = 0;
	else if(start.y % 2 == 0)
		dist.x = 0;
	if(!dist.y)
		return (dist.x > 0 ? EnemyMoveState::west : EnemyMoveState::east);
	else if (!dist.x)
		return (dist.y > 0 ? EnemyMoveState::north : EnemyMoveState::south);
	else if(abs(dist.y) >= abs(dist.x))
		return (dist.y >= 0 ? EnemyMoveState::north : EnemyMoveState::south);
	else
		return (dist.x >= 0 ? EnemyMoveState::west : EnemyMoveState::east);
}

EnemyMoveState Finder::findpath(Map map, sf::Vector2i start, sf::Vector2i end)
{
	EnemyMoveState estDir = calculatedirection(start, end);
	sf::Vector2i path(start.x,start.y);
	switch (estDir)
	{
	case EnemyMoveState::north:
		path.y -= 1;
		break;
	case EnemyMoveState::south:
		path.y += 1;
		break;
	case EnemyMoveState::west:
		path.x -= 1;
		break;
	case EnemyMoveState::east:
		path.x += 1;
		break;
	default:
		break;
	}
	if(map.tileAt(path) == Tile::Solid || (!_wallPass && map.tileAt(path) == Tile::Destructible) || (!_wallPass && map.tileAt(path) == Tile::Bomb))
		return (EnemyMoveState)(RNG::getRandomNumber(0, (NUM_MOVEMENT_STATES - 1)));
	return estDir;
}

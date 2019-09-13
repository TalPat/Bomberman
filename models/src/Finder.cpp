#include "../include/Finder.hpp"
#include <iostream>
const int NUM_MOVEMENT_STATES = 4;
const float AGGROTIME = 4;
const float DEFAULT_SPEED = 2.5;
const float AUTOSWITCH = 1;
const sf::Vector2f DEFAULT_START(9.5, 9.5);

Finder::Finder()		
{
	_position = (DEFAULT_START);
	_enemySpeed = (DEFAULT_SPEED);
	moveState = (EnemyMoveState::north);
	_switchTime = (AUTOSWITCH);
	type = (EnemyType::EFinder);
	_wallPass = (true);
	changeMoveState();
}

Finder::Finder(sf::Vector2f start)		
{
	_position = (start);
	_enemySpeed = (DEFAULT_SPEED);
	moveState = (EnemyMoveState::north);
	_switchTime = (AUTOSWITCH);
	type = (EnemyType::EFinder);
	_wallPass = (true);
	changeMoveState();
}

Finder::~Finder(){
	return;
}

void Finder::changeMoveState()
{
	this->moveState =(EnemyMoveState)(rand() % (NUM_MOVEMENT_STATES));
}
void Finder::changeMoveState(const Map &map, const Player &player){
	this->moveState = findpath(map, sf::Vector2i(this->position()), sf::Vector2i(player.position()));
}

void Finder::update(float deltaTime, const Map &map, const Player &player)
{
	_switchTime -= deltaTime;
	// _aggression -= deltaTime;
	// if(_aggression <= 0)
	// {
		// this->changeAggression();
	// }
	if((int)(this->position().x)%2 || (int)(this->position().y)%2)
			_switchTime = 0;
	if(_switchTime <= 0)
	{
		this->changeMoveState(map, player);
		// switch (this->moveState)
		// {
		// case EnemyMoveState::north:
		// 	std::cout << "N\n";
		// 	break;
		// case EnemyMoveState::south:
		// 	std::cout << "S\n";
		// 	break;
		// case EnemyMoveState::east:
		// 	std::cout << "E\n";
		// 	break;
		// case EnemyMoveState::west:
		// 	std::cout << "W\n";
		// 	break;
		// default:
		// 	break;
		// }
		// if(_aggression)
		// 	_switchTime = (rand() % (int)(AUTOSWITCH/2)) + 1;
		// else
		
			_switchTime = (rand() % (int)(AUTOSWITCH)) +1 ;
	}
	this->move(deltaTime, map);
}

void Finder::changeAggression()
{
	// _aggression = (rand() % 4);
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

EnemyMoveState Finder::calculatedirection(sf::Vector2i start, sf::Vector2i end){
    int dy = start.y - end.y;
    int dx = start.x - end.x;
    // std::cout << "dx ==> " << dx << "\n";
    // std::cout << "dy ==> " << dy << "\n";
	if(start.x%2 == 0)
		dy = 0;
	else if(start.y%2 == 0)
		dx = 0;
	
    if(!dy)
        return (dx > 0 ? EnemyMoveState::west:EnemyMoveState::east);
    else if (!dx)
        return (dy > 0 ? EnemyMoveState::north:EnemyMoveState::south );
    else if(abs(dy) <= abs(dx))
        return (dy >= 0 ? EnemyMoveState::north:EnemyMoveState::south );
    else/* if(abs(dx) > abs(dy))*/
        return (dx >= 0 ? EnemyMoveState::west:EnemyMoveState::east);
    /*else
        return EnemyMoveState::none;
    */
    
}
EnemyMoveState Finder::findpath(Map map, sf::Vector2i start, sf::Vector2i end){
    // sf::Vector2i estblock(start.x, start.y);
	EnemyMoveState estDir = calculatedirection(start, end);
    sf::Vector2i path(start.x,start.y);
        // findpath(map, start, end);
        switch (estDir)
        {
        case EnemyMoveState::north:
            path.y -= 1;
            // std::cout << "North"<<"\n";
            break;
        case EnemyMoveState::south:
            path.y += 1;
            // std::cout << "South"<<"\n";
            break;
        case EnemyMoveState::west:
            path.x -= 1;
            // std::cout << "West"<<"\n";
            break;
        case EnemyMoveState::east:
            path.x += 1;
            // std::cout << "East"<<"\n";
            break;
        default:
            break;
        }
        if(map.tileAt(path) == Tile::Solid || (!_wallPass && map.tileAt(path) == Tile::Destructible) || (!_wallPass && map.tileAt(path) == Tile::Bomb))
            return (EnemyMoveState)(rand() % (NUM_MOVEMENT_STATES));
    return estDir;
}
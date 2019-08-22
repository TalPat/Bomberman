#include "../include/Enemy.hpp"
#include "../include/Ballom.hpp"

#include <iostream>
const int NUM_STATES = 5;
const float AGGROTIME = 4;
const float DEFAULT_SPEED = 3.5;
const float AUTOSWITCH = 6;
const sf::Vector2f DEFAULT_START(9.5, 9.5);
		Ballom::Ballom()		
		{
			_position = (DEFAULT_START);
			_enemySpeed = (DEFAULT_SPEED);
			moveState = (EnemyMoveState::north);
			_switchTime = (AUTOSWITCH);
			// appears = ({1,2});
			type = (EnemyType::EBallom);
			changeMoveState();
		}
		Ballom::~Ballom(){
			return;
		}
		void Ballom::changeMoveState(){
			
			int num =(rand() % (NUM_STATES));
			if(num == EnemyMoveState::stand)
				num = (rand() % (NUM_STATES-1));
			moveState = num;
		}

		void Ballom::update(float deltaTime, const Map &map){
			_switchTime -= deltaTime;
			_aggression -= deltaTime;
			if(_aggression <= 0){
				this->changeAggression();
			}
			if(_switchTime <= 0){
				this->changeMoveState();
				_switchTime = AUTOSWITCH;
			}
			this->move(deltaTime, map);
		}
		
		void Ballom::changeAggression(){
			_aggression = (rand() % 4);
			if(_aggression == 3){
				_enemySpeed = DEFAULT_SPEED + 1.5;
				_aggression = AGGROTIME;
				type = EnemyType::EAggroBallom;
				std::cout << "AGGRO TIME!\n";
			}
			else
			{
					_enemySpeed = DEFAULT_SPEED;
					type = EnemyType::EBallom;
			}
			
		}
void Ballom::move(float deltaTime, const Map &map)
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
	if(moveState == EnemyMoveState::stand)
		_switchTime = 1;
	
	this->_position = this->_position + (movement * this->_enemySpeed * deltaTime);
	sf::Vector2i enemyCell(this->_position);

	for (sf::Vector2i direction : TEST_NEIGHBOURS)
	{
		sf::Vector2i cell = enemyCell + direction;
		Tile tile = map.tileAt(cell);
		if (!(tile == Tile::Clear || tile == Tile::Bomb || tile == Tile::Destructible))
		{
			if (correctEnemyCellCollision(cell)){
				break;
			}
		}
	}
}

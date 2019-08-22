#ifndef _Enemy_hpp_
#define _Enemy_hpp_

#include "Map.hpp"
#include "EnemyType.hpp"
#include <SFML/System.hpp>

enum EnemyMoveState
{
	north,
	east,
	south,
	west,
	stand
};
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
struct sRange{
	int min;
	int max;
};
class Enemy
{
 
protected:
	int points;
	sRange appears;
	sf::Vector2f _position;
	float _enemySpeed;
	float _switchTime;
	bool _wallPass;


public:
	EnemyType type;
	Enemy();
	~Enemy();
	bool correctEnemyCellCollision(sf::Vector2i cell);
	virtual void update(float deltaTime, const Map &map);
	int moveState;
	virtual void changeMoveState();
	virtual void changeAggression();
	virtual void move(float deltaTime, const Map &map);
	const sf::Vector2f &position() const;
};

#endif

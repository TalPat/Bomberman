#ifndef _Enemy_hpp_
#define _Enemy_hpp_

#include "Map.hpp"
#include <SFML/System.hpp>

enum EnemyMoveState
{
	north,
	east,
	south,
	west,
};
struct sRange{
	int min;
	int max;
};
class Enemy
{
	int points;
	sRange appears;
 
	sf::Vector2f _position;
protected:
	float _enemySpeed;
	float _switchTime;
	bool _wallPass;

public:
	Enemy();
	~Enemy();
	bool correctEnemyCellCollision(sf::Vector2i cell);
	void update(float deltaTime, const Map &map);
	int moveState;
	virtual void changeMoveState();
	virtual void move(float deltaTime, const Map &map);
	const sf::Vector2f &position() const;
};

#endif

#ifndef _Enemy_hpp_
#define _Enemy_hpp_

#include "Map.hpp"

#include <SFML/System.hpp>

struct EnemyMoveState
{
	bool north;
	bool east;
	bool south;
	bool west;
};

class Enemy
{
	sf::Vector2f _position;

	float _enemySpeed;
	float _switchTime;

	bool correctEnemyCellCollision(sf::Vector2i cell);

public:
	Enemy();
	~Enemy();

	EnemyMoveState moveState;
	void changeMoveState();
	void move(float deltaTime, const Map &map);
	void update(float deltaTime, const Map &map);
	const sf::Vector2f &position() const;
};

#endif

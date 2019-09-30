#ifndef _FINDER_HPP_
#define _FINDER_HPP_

#include "IEnemy.hpp"
#include <pthread.h>

class Finder : public IEnemy
{
public:
	Finder();
	Finder(sf::Vector2f start);
	~Finder();
	float _aggression;
	void changeMoveState();
	void changeMoveState(const Map &map, const Player &player);
	EnemyMoveState calculatedirection(sf::Vector2i start, sf::Vector2i end);
	EnemyMoveState findpath(Map map, sf::Vector2i start, sf::Vector2i end);
	void update(float deltaTime, const Map &map, const Player &player);
	void changeAggression();
	sf::Vector2i distance(sf::Vector2i start, sf::Vector2i end);
};
#endif
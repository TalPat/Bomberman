#ifndef _ENEMIES_HPP_
#define _ENEMIES_HPP_

#include "IEnemy.hpp"
#include "Map.hpp"
#include "Ballom.hpp"

#include <list>

class Enemies
{
public:
	std::list<IEnemy*> list;
	void updateAll(float deltaTime, const Map &map);
	void populate();
	void populate(int numEnemies);
	Enemies();
	~Enemies();
	void kill(sf::Vector2i killPosition); 
};
#endif

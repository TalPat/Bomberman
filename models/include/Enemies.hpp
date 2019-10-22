#ifndef _ENEMIES_HPP_
#define _ENEMIES_HPP_

#include "IEnemy.hpp"
#include "Map.hpp"
#include "Ballom.hpp"
#include "Finder.hpp"
#include <list>

class Enemies
{
public:
	std::list<IEnemy*> list;
	void updateAll(float deltaTime, const Map &map, Player &player);
	void populate();
	void populate(int numEnemies);
	void populate(int level, const Map &map);
	Enemies();
	~Enemies();
	void init(int level);
	void kill(const Map &map, Player &player); 

	std::string to_string();
	void from_string(std::istream &istream);
};
#endif

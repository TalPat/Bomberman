#ifndef _ENEMIESLIST_HPP_
# define _ENEMIESLIST_HPP_
# include "Enemy.hpp"
# include "Map.hpp"
# include "Ballom.hpp"
# include <list>
class EnemiesList{
	public:
		std::list<Enemy> eList;
		void updateAll(float deltaTime, const Map &map);
		void populate();
		// void populate(const Map &map);
		EnemiesList();
		~EnemiesList();
		
};
#endif

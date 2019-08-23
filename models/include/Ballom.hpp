#ifndef _BALLOM_HPP_
# define _BALLOM_HPP_
class Ballom:public IEnemy{
	public:
		Ballom();
		Ballom(sf::Vector2f start);
		~Ballom();
		float _aggression;
		void changeMoveState();
		void update(float deltaTime, const Map &map);
		void changeAggression();
};
#endif
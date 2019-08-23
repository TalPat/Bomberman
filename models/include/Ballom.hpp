#ifndef _BALLOM_HPP_
# define _BALLOM_HPP_
class Ballom:public Enemy{
	public:
		Ballom();
		Ballom(sf::Vector2f start);
		~Ballom();
		float _aggression;
		void changeMoveState();
		void update(float deltaTime, const Map &map);
		void changeAggression();
		void move(float deltaTime, const Map &map);
};
#endif
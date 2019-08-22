#ifndef _BALLOM_HPP_
# define _BALLOM_HPP_
class Ballom:public Enemy{
	public:
		Ballom();
		~Ballom();
		float _aggression;
		void changeMoveState();

		void update(float deltaTime, const Map &map);
		
		void changeAggression();
		void move(float deltaTime, const Map &map);
		// void move(float deltaTime, const Map &map);
};
#endif
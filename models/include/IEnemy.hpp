#ifndef _IEnemy_hpp_
#define _IEnemy_hpp_

#include "Map.hpp"
#include "Player.hpp"

#include "EnemyType.hpp"
#include <SFML/System.hpp>
#include <cmath>

enum EnemyMoveState
{
	north,
	east,
	south,
	west
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

struct sRange
{
	int min;
	int max;
};

class IEnemy
{
 
protected:
	int points;
	sRange appears;
	sf::Vector2f _position;
	float _enemySpeed;
	float _switchTime;
	bool _wallPass;
	sf::Clock lifeClock;
	int id;
public:
	static int idCounter;
	EnemyType type;
	IEnemy();
	IEnemy(sf::Vector2f start);
	~IEnemy();
	bool correctEnemyCellCollision(sf::Vector2i cell);
	virtual void update(float deltaTime, const Map &map, const Player &player);
	EnemyMoveState moveState;
	virtual void changeMoveState();
	virtual void changeAggression();
	void move(float deltaTime, const Map &map);
	const sf::Vector2f &position() const;
	bool operator == (const IEnemy& e) const { return this->_position == e._position; }

	sf::Clock getLifeClock(void);
	int getid(void);

	std::string to_string();
	void from_string(std::istream &istream);
};
#endif

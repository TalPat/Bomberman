#ifndef _Player_hpp_
#define _Player_hpp_

#include "Map.hpp"

#include <cmath>
#include <SFML/System.hpp>

struct MoveState
{
	bool north;
	bool east;
	bool south;
	bool west;
};

class Player
{
	float _playerSpeed;
	sf::Vector2f _position;

public:
	Player();
	~Player();

	MoveState moveState;

	void init(int level);
	void move(float deltaTime, const Map &map);
	const sf::Vector2f &position() const;
};

#endif
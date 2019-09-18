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
	bool _alive;
	float _lives;
	float _deathTime;
	sf::Vector2f _position;

public:
	Player();
	~Player();

	MoveState moveState;

	void kill(void);
	void init(int level);
	void handleMovement(float deltaTime, const Map &map);
	void update(float deltaTime, const Map &map);
	void addLife(void);
	bool isAlive(void) const;
	const sf::Vector2f &position() const;
};

#endif
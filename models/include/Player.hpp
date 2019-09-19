#ifndef _Player_hpp_
#define _Player_hpp_

#include "Map.hpp"
#include "EngineEvent.hpp"

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
	int _lives;
	int _bombRange;
	int _maxBombs;
	sf::Vector2f _position;

public:
	Player();
	~Player();

	MoveState moveState;

	void addBombRange(void);
	void addMaxBombs(void);
	int getBombRange(void) const;
	int getMaxBombs(void) const;
	void kill(void);
	void init(int level);
	void handleMovement(float deltaTime, const Map &map);
	void update(float deltaTime, const Map &map);
	void addLife(void);
	bool isAlive(void) const;
	const sf::Vector2f &position() const;
};

#endif
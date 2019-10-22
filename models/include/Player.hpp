#ifndef _Player_hpp_
#define _Player_hpp_

#include "Map.hpp"
#include "EngineEvent.hpp"
// #include "Sound.hpp"

#include <sstream>
#include <cmath>
#include <SFML/System.hpp>

struct MoveState
{
	bool north;
	bool east;
	bool south;
	bool west;
};

struct PreviousState
{
	int _bombRange;
	int _maxBombs;
	int _score;
};

class Player
{
	float _playerSpeed;
	bool _alive;
	int _lives;
	int _bombRange;
	int _maxBombs;
	int _score;
	sf::Vector2f _position;
	// Sound sound;

public:
	Player();
	~Player();

	PreviousState previousState;
	MoveState moveState;

	std::string to_string();
	void from_string(std::istream &istream);

	void addBombRange(void);
	void addMaxBombs(void);
	int getBombRange(void) const;
	int getMaxBombs(void) const;
	void kill(void);
	void init(int level);
	void handleMovement(float deltaTime, const Map &map);
	void update(float deltaTime, const Map &map);
	void addLives(int lives);
	void addScore(int score);
	int getLives(void) const;
	int getScore(void) const;
	bool isAlive(void) const;
	const sf::Vector2f &position() const;
};

#endif
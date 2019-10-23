#include "../include/Player.hpp"

#include <iostream>

const sf::Vector2f DEFAULT_START(1.5, 1.5);
const float DEFAULT_SPEED = 5;
const float HALF_WIDTH = 0.35;

Player::Player() : _position(DEFAULT_START),
					_playerSpeed(DEFAULT_SPEED),
					_lives(3),
					moveState({false, false, false, false}),
					_alive(true),
					_bombRange(2),
					_maxBombs(1),
					_score(0)
{
}

Player::~Player()
{
}

void Player::init(int level)
{
	this->_alive = true;
	this->_position = DEFAULT_START;
	this->moveState = {false, false, false, false};
	this->previousState = {this->_bombRange, this->_maxBombs, this->_score};
	if (level != 0 && level % 4 == 0)
	{
		this->_lives += 1;
	}
}

void Player::kill(void)
{
	// sound.playSound(sad);
	this->_lives--;
	this->_alive = false;
	this->_bombRange = this->previousState._bombRange;
	this->_maxBombs = this->previousState._maxBombs;
	this->_score = this->previousState._score;		
}

void Player::handleMovement(float deltaTime, const Map &map)
{
	MoveState &move = this->moveState;
	sf::Vector2f &pos = this->_position;

	// Determine movement vectors
	sf::Vector2f dx(0 + move.east - move.west, 0);
	sf::Vector2f dy(0, 0 + move.south - move.north);

	sf::Vector2i north = sf::Vector2i( pos + sf::Vector2f(0.0, -0.6) );
	sf::Vector2i south = sf::Vector2i( pos + sf::Vector2f(0.0, 0.6) );
	sf::Vector2i west = sf::Vector2i( pos + sf::Vector2f(-0.6, 0.0) );
	sf::Vector2i east = sf::Vector2i( pos + sf::Vector2f(0.6, 0.0) );
	if (move.south && map.tileAt( south ) == Tile::Clear )
		dx.x += 0.8 * ((south.x + 0.5) - pos.x);
	if (move.north && map.tileAt( north ) == Tile::Clear )
		dx.x += 0.8 * ((north.x + 0.5) - pos.x);
	if (move.east && map.tileAt( east ) == Tile::Clear )
		dy.y += 0.8 * ((east.y + 0.5) - pos.y);
	if (move.west && map.tileAt( west ) == Tile::Clear )
		dy.y += 0.8 * ((west.y + 0.5) - pos.y);

	// Scale movement vectors
	dx *= this->_playerSpeed * deltaTime;
	dy *= this->_playerSpeed * deltaTime;


	auto comp = [](Tile tile) {
		return tile != Tile::Clear && tile != Tile::BombClear && tile != Tile::Flame;
	};
	// Move player as far as possible without colliding
	if (dx.x != 0 && dy.y != 0 && map.lerpCollide(pos, dx + dy, HALF_WIDTH, comp))
		return;
	if (dx.x != 0 && map.lerpCollide(pos, dx, HALF_WIDTH, comp))
		return;
	if (dy.y != 0 && map.lerpCollide(pos, dy, HALF_WIDTH, comp))
		return;
}

void Player::update(float deltaTime, const Map &map)
{
	if (this->_alive == false)
	{
		return;
	}

	this->handleMovement(deltaTime, map);
	
	// kill player on flame collisions
	auto compFlame = [](Tile tile) {
		return tile == Tile::Flame;
	};
	if (map.collide(this->_position, HALF_WIDTH - 0.2, compFlame))
		this->kill();
}

int Player:: getLives(void) const
{
	return this->_lives;
}

int Player:: getScore(void) const
{
	return this->_score;
}

int Player::getBombRange(void) const
{
	return this->_bombRange;
}

int Player::getMaxBombs(void) const
{
	return this->_maxBombs;
}

void Player::addBombRange(void)
{
	this->_bombRange++;
}

void Player::addMaxBombs(void)
{
	this->_maxBombs++;
}

void Player::addScore(int score)
{
	this->_score += score;	
}

void Player::addLives(int lives)
{
	this->_lives += lives;
}

bool Player::isAlive(void) const
{
	return this->_alive;
}

const sf::Vector2f &Player::position() const
{
	return this->_position;
};

std::string Player::to_string()
{
	std::ostringstream sstream;

	sstream << this->_playerSpeed << " "
			<< this->_alive << " "
			<< this->_lives << " "
			<< this->_bombRange << " "
			<< this->_maxBombs << " "
			<< this->_score << " "
			<< this->_position.x << " "
			<< this->_position.y << '\n';
	return sstream.str();
}

void Player::from_string(std::istream &istream)
{
	istream >> this->_playerSpeed
			>> this->_alive
			>> this->_lives
			>> this->_bombRange
			>> this->_maxBombs
			>> this->_score
			>> this->_position.x
			>> this->_position.y;
}

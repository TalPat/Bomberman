#include "../include/Player.hpp"

const sf::Vector2f DEFAULT_START(1.5, 1.5);
const float DEFAULT_SPEED = 5;

Player::Player() : _position(DEFAULT_START),
				   _playerSpeed(DEFAULT_SPEED),
				   moveState({false, false, false, false})
{
}

Player::~Player()
{
}

void Player::init(int level)
{
	this->_position = DEFAULT_START;
	this->moveState = {false, false, false, false};
}

void Player::move(float deltaTime, const Map &map)
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
		return tile != Tile::Clear && tile != Tile::BombClear;
	};
	// Move player as far as possible without colliding
	if (dx.x != 0 && dy.y != 0 && map.lerpCollide(pos, dx + dy, 0.35, comp))
		return;
	if (dx.x != 0 && map.lerpCollide(pos, dx, 0.35, comp))
		return;
	if (dy.y != 0 && map.lerpCollide(pos, dy, 0.35, comp))
		return;
}

const sf::Vector2f &Player::position() const
{
	return this->_position;
};

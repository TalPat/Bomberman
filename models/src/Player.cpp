#include "../include/Player.hpp"

const sf::Vector2f DEFAULT_START(1.5, 1.5);
const float DEFAULT_SPEED = 4;

Player::Player() : _position(DEFAULT_START),
				   _playerSpeed(DEFAULT_SPEED),
				   moveState({false, false, false, false})
{
}

Player::~Player()
{
}

void Player::move(float deltaTime, const Map &map)
{
	MoveState &move = this->moveState;

	// Determine movement vectors
	sf::Vector2f dx(0 + move.east - move.west, 0);
	sf::Vector2f dy(0, 0 + move.south - move.north);

	// Scale movement vectors
	dx *= this->_playerSpeed * deltaTime;
	dy *= this->_playerSpeed * deltaTime;


	auto comp = [](Tile tile) {
		return tile != Tile::Clear && tile != Tile::BombClear;
	};
	// Move player as far as possible without colliding
	sf::Vector2f &pos = this->_position;
	if (dx.x != 0 && dy.y != 0 && map.lerpCollide(pos, dx + dy, 0.40, comp))
		return;
	if (dx.x != 0 && map.lerpCollide(pos, dx, 0.40, comp))
		return;
	if (dy.y != 0 && map.lerpCollide(pos, dy, 0.40, comp))
		return;
}

const sf::Vector2f &Player::position() const
{
	return this->_position;
};

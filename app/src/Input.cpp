#include "./Input.hpp"

Input::Input() : _up(Key::Up),
				 _down(Key::Down),
				 _left(Key::Left),
				 _right(Key::Right),
				 _bomb(Key::Space)
{}

Input::~Input() {}

EngineEvent Input::getInput(Key key)
{
	if (key == this->_up)
		return EngineEvent::move_up;
	else if (key == this->_down)
		return EngineEvent::move_down;
	else if (key == this->_left)
		return EngineEvent::move_left;
	else if (key == this->_right)
		return EngineEvent::move_right;
	else if (key == this->_bomb)
		return EngineEvent::place_bomb;
	else
		return EngineEvent::unknown;
}

Key Input::getUp() const
{
	return this->_up;
}

void Input::setUp(Key key)
{
	this->_up = key;
}

Key Input::getDown() const
{
	return this->_down;
}

void Input::setDown(Key key)
{
	this->_down = key;
}

Key Input::getLeft() const
{
	return this->_left;
}

void Input::setLeft(Key key)
{
	this->_left = key;
}

Key Input::getRight() const
{
	return this->_right;
}

void Input::setRight(Key key)
{
	this->_right = key;
}

Key Input::getBomb() const
{
	return this->_bomb;
}

void Input::setBomb(Key key)
{
	this->_bomb = key;
}

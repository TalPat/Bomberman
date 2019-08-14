#include "./Input.hpp"

#include <iostream>

Input::Input() : _up(Key::Up),
				 _down(Key::Down),
				 _left(Key::Left),
				 _right(Key::Right),
				 _bomb(Key::Space),
				 _pause(Key::Escape)
{
}

Input::~Input() {}

// Need to be modified later
InputResponse Input::parseKeys(std::vector<EngineEvent> &engineEvents, sf::RenderWindow &window)
{
	sf::Event event;
	// TODO: Break into functions
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case event.KeyPressed:
		{
			Key key = event.key.code;
			if (key == this->_up)
				engineEvents.push_back(EngineEvent::move_up);
			else if (key == this->_left)
				engineEvents.push_back(EngineEvent::move_left);
			else if (key == this->_down)
				engineEvents.push_back(EngineEvent::move_down);
			else if (key == this->_right)
				engineEvents.push_back(EngineEvent::move_right);
			else if (key == this->_pause)
				return InputResponse::pause;
			break;
		}
		case event.KeyReleased:
		{
			Key key = event.key.code;
			if (key == this->_up)
				engineEvents.push_back(EngineEvent::stop_up);
			else if (key == this->_left)
				engineEvents.push_back(EngineEvent::stop_left);
			else if (key == this->_down)
				engineEvents.push_back(EngineEvent::stop_down);
			else if (key == this->_right)
				engineEvents.push_back(EngineEvent::stop_right);
			break;
		}
		case event.Closed:
			return InputResponse::quit;
		default:
			break;
		}
	}
	return InputResponse::resume;
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

Key Input::getPause() const
{
	return this->_pause;
}

void Input::setPause(Key key)
{
	this->_pause = key;
}

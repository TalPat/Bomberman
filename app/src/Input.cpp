#include "./Input.hpp"

#include <iostream>

Input::Input() : _up(Key::Up),
				 _down(Key::Down),
				 _left(Key::Left),
				 _right(Key::Right),
				 _bomb(Key::Space),
				 _pause(Key::Escape)
{
	this->keyMap[Key::Up] = EngineEvent::move_up;
	this->keyMap[Key::Down] = EngineEvent::move_down;
	this->keyMap[Key::Left] = EngineEvent::move_left;
	this->keyMap[Key::Right] = EngineEvent::move_right;
	this->keyMap[Key::Space] = EngineEvent::move_up;
}

Input::~Input() {}

// Need to be modified later
InputResponse Input::parseKeys(std::vector<EngineEvent> &engineEvents, sf::RenderWindow &window)
{
	sf::Event event;
	EngineEvent eEvent = EngineEvent::unknown;
	// TODO: Break into functions
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case event.KeyPressed:
		{
			Key key = event.key.code;
			if (key == this->_pause)
				return InputResponse::pause;

			eEvent = this->keyMap[key];
			if (eEvent != EngineEvent::unknown)
				engineEvents.push_back(eEvent);

			break;
		}
		case event.KeyReleased:
		{
			Key key = event.key.code;

			eEvent = this->keyMap[key];
			if (eEvent != EngineEvent::unknown && eEvent < EngineEvent::place_bomb)
				engineEvents.push_back(EngineEvent(eEvent + 1));

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

void Input::saveConfig() const
{
	std::ofstream file;
	std::string path = SETTINGS_DIR + std::string("/input_map.txt");
	file.open(path);
	file << this->_up << std::endl;
	file << this->_down << std::endl;
	file << this->_left << std::endl;
	file << this->_right << std::endl;
	file << this->_bomb << std::endl;
	file.close();
}

void Input::loadConfig()
{
	std::ifstream file;
	std::string path = SETTINGS_DIR + std::string("/input_map.txt");
	std::string in;
	int key;
	int up;
	int down;
	int left;
	int right;
	int bomb;
	file.open(path);

	file >> up >> down >> left >> right >> bomb;

	this->setUp(Key(up));
	this->setDown(Key(down));
	this->setLeft(Key(left));
	this->setRight(Key(right));
	this->setBomb(Key(bomb));

	file.close();
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

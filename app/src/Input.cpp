#include "./Input.hpp"

#include <iostream>

Input::Input() : _pause(Key::Escape)
{
	this->keyMap[Key::Up] = EngineEvent::move_up;
	this->keyMap[Key::Down] = EngineEvent::move_down;
	this->keyMap[Key::Left] = EngineEvent::move_left;
	this->keyMap[Key::Right] = EngineEvent::move_right;
	this->keyMap[Key::Space] = EngineEvent::move_up;
}

Input::~Input() {}

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
	std::string path = SETTINGS_DIR + std::string("/input_map.cfg");
	std::ofstream os(path, std::ios::binary);

	cereal::BinaryOutputArchive archive(os);

	Input input = *this;
	archive(CEREAL_NVP(input));
}

void Input::loadConfig()
{
	std::string path = SETTINGS_DIR + std::string("/input_map.cfg");
	std::ifstream is(path, std::ios::binary);

	cereal::BinaryInputArchive archive_in(is);
	archive_in(this->keyMap);
}

void Input::setKey(EngineEvent event, Key key)
{
	EngineEvent current = this->keyMap[key];

	// Handle stop_events being set
	// This is more of a usage error than a runtime error
	if (event % 2 == 0)
		throw std::runtime_error("Cannot set stop events");

	// Only set key if it hasn't already been mapped
	if (current == EngineEvent::unknown)
	{
		this->removeMapping(event);
		this->keyMap[key] = event;
	}
	else
	{
		throw std::runtime_error("Key already used");
	}
}

void Input::removeMapping(EngineEvent event)
{
	std::map<Key, EngineEvent>::iterator it = this->keyMap.begin();

	while (it != this->keyMap.end())
	{
		if (it->second == event)
		{
			this->keyMap.erase(it);
		}

		it++;
	}
}

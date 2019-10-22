#include "./Input.hpp"

#include <iostream>

Input::Input() : _pause(Key::Escape)
{
	this->keyMap = {
		{ Key::Up, EngineEvent::move_up },
		{ Key::Down, EngineEvent::move_down },
		{ Key::Left, EngineEvent::move_left },
		{ Key::Right, EngineEvent::move_right },
		{ Key::Space, EngineEvent::place_bomb }
	};
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

	try
	{
		Input input = *this;
		archive(CEREAL_NVP(input));
	}
	catch (const std::exception& e)
	{}
}

void Input::loadConfig(ControlMenu &ctrlMenu)
{
	std::string path = SETTINGS_DIR + std::string("/input_map.cfg");
	std::ifstream is(path, std::ios::binary);

	try
	{
		cereal::BinaryInputArchive archive_in(is);
		archive_in(this->keyMap);

		for (auto const &k : this->keyMap)
		{
			ctrlMenu.setControl(k.second, k.first);
		}
	}
	catch (const std::exception &e)
	{}
}

void Input::setKey(EngineEvent event, Key key)
{
	EngineEvent current = this->keyMap[key];

	// Handle stop_events being set
	// This is more of a usage error than a runtime error
	if (event % 2 == 0)
		throw std::runtime_error("Cannot set stop events");

	if (key == Key::Escape)
		throw std::runtime_error("Cannot set Escape key");

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
			break;
		}

		it++;
	}
}

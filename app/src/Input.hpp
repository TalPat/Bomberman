#ifndef _Input_hpp_
#define _Input_hpp_

#include <EngineEvent.hpp>
#include "ControlMenu.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

#include <cereal/archives/binary.hpp>
#include <cereal/types/map.hpp>

#include <map>
#include <fstream>

typedef sf::Keyboard::Key Key;

enum InputResponse
{
	resume,
	quit,
	pause
};

class Input
{
private:
	Key _pause;

	std::map<Key, EngineEvent> keyMap;

	void removeMapping(EngineEvent event);

public:
	Input();
	~Input();

	template <class Archive>
	void serialize(Archive &ar)
	{
		ar(this->keyMap);
	}

	InputResponse parseKeys(std::vector<EngineEvent> &engineEvents, sf::RenderWindow &window);

	void saveConfig() const;
	void loadConfig(ControlMenu &ctrlMenu);

	// Throws a runtime_error if key is already mapped
	void setKey(EngineEvent event, Key key);

	// TODO: Maybe add function to get Key
	// that returns a string representation of said Key
	// for display in a menu.
};

#endif

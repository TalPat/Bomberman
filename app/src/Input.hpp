#ifndef _Input_hpp_
#define _Input_hpp_

#include <EngineEvent.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>

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
	Key _up;
	Key _down;
	Key _left;
	Key _right;
	Key _bomb;
	Key _pause;

	std::map<Key, EngineEvent> keyMap;

	void removeMapping(EngineEvent event);

public:
	Input();
	~Input();

	InputResponse parseKeys(std::vector<EngineEvent> &engineEvents, sf::RenderWindow &window);

	// void saveConfig() const;
	// void loadConfig();

	// Throws a runtime_error if key is already mapped
	void setKey(EngineEvent event, Key key);

	// TODO: Maybe add function to get Key that returns a string representation.

	Key getUp() const;
	void setUp(Key key);

	Key getDown() const;
	void setDown(Key key);

	Key getLeft() const;
	void setLeft(Key key);

	Key getRight() const;
	void setRight(Key key);

	Key getBomb() const;
	void setBomb(Key key);
};

#endif

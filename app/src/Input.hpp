#ifndef _Input_hpp_
#define _Input_hpp_

#include <EngineEvent.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>

#include <map>

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

public:
	Input();
	~Input();

	InputResponse parseKeys(std::vector<EngineEvent> &engineEvents, sf::RenderWindow &window);
	// EngineEvent getInput(Key key);

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

	Key getPause() const;
	void setPause(Key key);
};

#endif

#ifndef _ENGINE_HPP
#define _ENGINE_HPP

#include "./EngineEvent.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>


// TODO: Bomb class etc..
struct Bomb   { int x; int y; int tick; };

class Engine
{
private:
public:
    // TODO: Use OOP and move into classes, use getters/setters etc..
    float x; // Player class
    float y;

    int width; // Map class
    int height;
    int *map;
    int getMapAt(int x, int y);
    void setMapAt(int x, int y, int val);

     // Bomb, TODO: put into class
     // void tick(deltatime);
    std::list<Bomb> bombs;

    long now; // Deltatime vars, TODO: ? move back up into bomberman or AMainLoop
    long dt;

	// deltaTime should be expressed in seconds
	// action might need to be vector as multiple keys can be pressed
	// in a single frame
	void update();
    Engine();
    ~Engine();
};

#endif

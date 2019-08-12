#ifndef _Bomberman_hpp_
#define _Bomberman_hpp_

#include "./AMainLoop.hpp"
#include <GameState.hpp>

#include <Engine.hpp>
#include <EngineEvent.hpp>
#include <Renderer.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include <map>
#include <ctime>

static const uint WINDOW_WIDTH = 640;
static const uint WINDOW_HEIGHT = 400;
static const char *WINDOW_TITLE = "Bomberman";

class Bomberman : private AMainLoop
{

private:
	sf::RenderWindow window;
	Engine engine;
	Renderer renderer;

    GameState state;
    
    // honestly not sure where the best place is to put this...
    // TODO: this should be in a settings class later
    std::map< sf::Keyboard::Key, EngineEvent > key_map
     = {
        { sf::Keyboard::Up,    EngineEvent::UP },
        { sf::Keyboard::Down,  EngineEvent::DOWN },
        { sf::Keyboard::Left,  EngineEvent::LEFT },
        { sf::Keyboard::Right, EngineEvent::RIGHT },
        { sf::Keyboard::Space, EngineEvent::ACTION }
    };
    
    double now; // Deltatime vars
    double dt;

	virtual void updateFunc();

public:
	Bomberman();
	~Bomberman();

	void startGame();
};

#endif

#include "../include/Engine.hpp"

#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

Engine::Engine() { 
    this->keys = new bool[EngineEvent::COUNT];
}

Engine::~Engine() {
    delete this->keys;
}

void Engine::loadLevel(GameState &game, int level) {
    // This will be changed significantly
    // TODO: discuss level loading/switching
    if (level == 0) {
        game.pos = sf::Vector2f(1.01, 1.01);
        game.initMap(21, 21);
        // TODO: In Map Class, change tile values, 0, 1, 2 to an enum
        for (int i = 0; i < game.height; ++i)
        {
            for (int j = 0; j < game.width; ++j)
            {
                if (i==0 || i==game.width-1 || j==0 || j==game.height-1) {
                    game.setTile(i, j, 1); // border
                } else if (i % 2 == 0 && j % 2 == 0) {
                    game.setTile(i, j, 1); // solid walls
                } else {
                    game.setTile(i, j, 0); // clear
                    if (rand() % 5 == 0 && (i > 3 || j > 3)) {
                        game.setTile(i, j, 2); // destructible walls
                    }
                }
            }
        }
    }
}

void Engine::key_pressed( EngineEvent event, GameState &game, double dt ) {
    bool held = this->keys[event];

    // TODO: proper mode handling
    // There needs to be state handling(i.e. main menu, playing, paused etc..)
    //if (level == MAIN_MENU)
    //    handleMainMenu();
    //else if (level == ...)
    //    hanlde...();
    if (game.mode == 0) { 
        if (!held && event == EngineEvent::ACTION) {
            game.mode++;
            loadLevel(game, 0);
        }
        // TODO: Implement proper menu selection logic
        else if (!held && event == EngineEvent::UP){
            game.option--;
        }
        else if (!held && event == EngineEvent::DOWN){  
            game.option++;
        }
        if (game.option < 0) game.option = 0;
        if (game.option > 4) game.option = 4;
    } else if (game.mode == 1) {
    // else if (game.mode == PLAYING) ...
        // TODO: change '< 1' to amount of bombs that can be placed
        if (!held && event == EngineEvent::ACTION && game.bombs.size() < 1) {
            game.placeBomb();
        }
    }
    // Set key
    this->keys[event] = true;
}

void Engine::key_released( EngineEvent event, GameState &game, double dt ) {
    // Handle the event
    // ...Your event code here...

    // Set key
    this->keys[event] = false;
}


void Engine::tickGame(double dt, GameState &game) {

    game.tickBombs(dt);

    // TODO: Change player movement to direction, vector based 
    // handle keyboard for movement
    // TODO: put in function
    game.movePlayer(keys, 2.5f * dt); // 2.5f here is player speed, move to gamestate
}

void Engine::update(double dt, GameState &game)
{
    if (game.mode == 1)
        tickGame(dt, game);
}

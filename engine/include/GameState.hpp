#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "./EngineEvent.hpp"

#include <SFML/System.hpp>
#include <iostream>
#include <list>

// TODO: Change to OOP possibly


struct Bomb   { int x; int y; double tick; };

// We could honestly save a week of work by just doing the following:
struct GameState
{
    // TODO: Discuss menus, gamestate switching etc..
    // TODO: write function that can change modes 
    // resets options/variables etc..
    int mode = 0;
    int option = 0; // prototype option selection



    // Player
    sf::Vector2f pos;
    void movePlayer(bool *keys, float dd) {
        if (keys[EngineEvent::LEFT]  && !getTile( pos.y+0.5, pos.x+0.2-dd ) ) pos.x -= dd;
        if (keys[EngineEvent::RIGHT] && !getTile( pos.y+0.5, pos.x+0.8+dd ) ) pos.x += dd;
        if (keys[EngineEvent::UP]    && !getTile( pos.y+0.2-dd, pos.x+0.5 ) ) pos.y -= dd;
        if (keys[EngineEvent::DOWN]  && !getTile( pos.y+0.8+dd, pos.x+0.5 ) ) pos.y += dd;
    }

    // Bombs
    std::list<Bomb> bombs;
    void tickBombs(float dt) {
        std::list<Bomb>::iterator i = bombs.begin();
        while (i != bombs.end())
        {
            (*i).tick += dt; // update bomb tick with game deltatime
            // When bomb reaches end of life, remove walls, remove bomb from bomb list
            if ((*i).tick > 2.6) {
                explodeBomb((*i).x, (*i).y, 1);
                // last parameter here is size ^^
                // should be changed based in powerup or something later
                bombs.erase(i++);
            }
            else
                i++;
        }
    }
    void placeBomb() {
        // place bomb at current player position
        Bomb new_bomb = {
            .x = (int)(pos.x+0.5),
            .y = (int)(pos.y+0.5),
            .tick = 0
        };
        bombs.push_back(new_bomb);
    }
    void explodeBomb(float x, float y, int size) {
        for (int i = 0; i < size; ++i)
        {
            if (getTile( y + i, x ) == 2) setTile( y + i, x, 0);
            if (getTile( y - i, x ) == 2) setTile( y - i, x, 0);
            if (getTile( y, x - i ) == 2) setTile( y, x - i, 0);
            if (getTile( y, x + i ) == 2) setTile( y, x + i, 0);
        }
    }



    // Map
    int width;
    int height;
    int *walls;
    void initMap(int w, int h) {
        width = w;
        height = h;
        walls = new int[w * h];
    }
    int getTile(int x_coord, int y_coord) {
        return this->walls[y_coord * width + x_coord];
    }
    void setTile(int x_coord, int y_coord, int val) {
        this->walls[y_coord * width + x_coord] = val;
    }
};

#endif
#include "../include/Bombs.hpp"

#include <iostream>

const float START_TIME = 2.6;
const float EXPLODE_TIME = 0.1;
const int MAX_BOMBS = 1;
const int BOMB_RANGE = 1;

Bombs::Bombs() {}
Bombs::~Bombs() {}

void Bombs::addBomb(sf::Vector2f pos) {
    if (bomb_list.size() < MAX_BOMBS) {
        Bomb new_bomb = {
            .position = sf::Vector2i((int)pos.x, (int)pos.y),
            .tick = START_TIME,
        };
        bomb_list.push_back(new_bomb);
    }
}
    
void Bombs::update(float dt, Map &map) {
    std::list<Bomb>::iterator bb = bomb_list.begin();
    while (bb != bomb_list.end())
    {
        bb->tick -= dt; // update bomb tick with game deltatime
        if (bb->tick < EXPLODE_TIME) {
            for (int i = 1; i < BOMB_RANGE + 1; ++i) // TODO: change to bomb size
            {
                if (map.tileAt( bb->position + sf::Vector2i(i,0)) == Tile::Destructible)
                    map.setTile(bb->position + sf::Vector2i(i,0), Tile::Clear);
                if (map.tileAt( bb->position + sf::Vector2i(-i,0)) == Tile::Destructible)
                    map.setTile(bb->position + sf::Vector2i(-i,0), Tile::Clear);
                if (map.tileAt( bb->position + sf::Vector2i(0,i)) == Tile::Destructible)
                    map.setTile(bb->position + sf::Vector2i(0,i), Tile::Clear);
                if (map.tileAt( bb->position + sf::Vector2i(0,-i)) == Tile::Destructible)
                    map.setTile(bb->position + sf::Vector2i(0,-i), Tile::Clear);
            }
        }
        if (bb->tick < 0.0) {
            bomb_list.erase(bb++);
        }
        else
            bb++;
    }
}
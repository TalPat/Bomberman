
#ifndef BOMBS_HPP
#define BOMBS_HPP

#include "../include/Map.hpp"


#include <list>
#include <SFML/System.hpp>

struct Bomb
{
    sf::Vector2i position;
    float tick;
};

class Bombs
{

public:
    Bombs();
    ~Bombs();

    std::list<Bomb> bomb_list;
    void addBomb(sf::Vector2f pos);
    void update(float dt, Map &map);
};

#endif

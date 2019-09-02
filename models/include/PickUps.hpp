#ifndef PICKUPS_HPP
#define PICKUPS_HPP

#include "Map.hpp"
#include "Player.hpp"

#include <list>

struct sPickUp
{
    sf::Vector2i position;
    enum PickUpType;
};

class PickUps
{
private:
    std::list<sPickUp> _pickups;

public:
    PickUps();
    void placePickUp(const Player &player, Map &map);
    void update(float deltaTime, Map &map);
};

#endif

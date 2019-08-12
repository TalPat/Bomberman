#ifndef I_COLLIDER_HPP
#define I_COLLIDER_HPP

#include <SFML/System.hpp>

class ICollider
{
private:
    sf Vector2f pos; // position in the world, centred in the model, wall etc..
public:
    ICollider(sf::Vector2f p) : pos(p);
    ~ICollider();
};

#endif
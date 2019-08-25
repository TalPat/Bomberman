#ifndef I_COLLIDER_HPP
#define I_COLLIDER_HPP

#include <SFML/System.hpp>

class ICollider
{
public:
    virtual bool collide(const sf::Vector2f &pos, float radius) const = 0;
};

#endif

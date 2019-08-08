
#include "../include/Engine.hpp"

#include <iostream>

Engine::Engine() {
    this->x = 1;
    this->y = 1;
    this->width = 21;
    this->height = 21;
    this->map = new int[this->width * this->height];
    // TODO: In Map Class, change tile values, 0, 1, 2 to an enum
    for (int i = 0; i < this->height; ++i)
    {
        for (int j = 0; j < this->width; ++j)
        {
            if (i==0 || i==this->width-1 || j==0 || j==this->height-1) {
                setMapAt(i, j, 1); // border
            } else if (i % 2 == 0 && j % 2 == 0) {
                setMapAt(i, j, 1); // solid walls
            } else {
                setMapAt(i, j, 0); // clear
                if (rand() % 5 == 0 && (i > 3 || j > 3)) {
                    setMapAt(i, j, 2); // destructible walls
                }
            }
        }
    }
    std::cout << "test" << "\n";
}

Engine::~Engine() {
    delete map;
}

void Engine::setMapAt(int x_coord, int y_coord, int val) {
    this->map[ y_coord * this->width + x_coord ] = val;
}

int Engine::getMapAt(int x_coord, int y_coord) {
    return this->map[ y_coord * this->width + x_coord ];
}

// TODO: We need a consistent way of determining whether a key was released pressed
bool spaceDown = false;
void Engine::update()
{
    // update bombs
    std::list<Bomb>::iterator i = this->bombs.begin();
    while (i != this->bombs.end())
    {
        (*i).tick += this->dt; // update bomb tick with game deltatime
        // When bomb reaches end of life, remove walls, remove bomb from bomb list
        if ((*i).tick > 26000) {
            if (getMapAt( ((*i).y+1), ((*i).x) ) == 2) setMapAt( ((*i).y+1), ((*i).x), 0);
            if (getMapAt( ((*i).y-1), ((*i).x) ) == 2) setMapAt( ((*i).y-1), ((*i).x), 0);
            if (getMapAt( ((*i).y), ((*i).x+1) ) == 2) setMapAt( ((*i).y), ((*i).x+1), 0);
            if (getMapAt( ((*i).y), ((*i).x-1) ) == 2) setMapAt( ((*i).y), ((*i).x-1), 0);
            this->bombs.erase(i++);
        }
        else
            i++;
    }
    // bomb keyboard interaction
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && spaceDown == false && this->bombs.size() < 1 ) {
        Bomb new_bomb = { .x = (int)(x+0.5), .y = (int)(y+0.5), .tick = 0 };
        this->bombs.push_back(new_bomb);
        spaceDown = true;
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        spaceDown = false;
    }

    // TODO: Change player movement to direction, vector based 
    // handle keyboard for movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  this->x -= 0.00035f * this->dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) this->x += 0.00035f * this->dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    this->y -= 0.00035f * this->dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  this->y += 0.00035f * this->dt;
    // movement collision detection
    if (getMapAt((this->y + 0.1), (this->x + 0.5)) == 0) this->y -= 0.00035f * this->dt;
    if (getMapAt((this->y + 0.9), (this->x + 0.5)) == 0) this->y += 0.00035f * this->dt;
    if (getMapAt((this->y + 0.5), (this->x + 0.1)) == 0) this->x -= 0.00035f * this->dt;
    if (getMapAt((this->y + 0.5), (this->x + 0.9)) == 0) this->x += 0.00035f * this->dt;
}

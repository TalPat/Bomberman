
#include "../include/Renderer.hpp"

#include <cmath>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// TODO: COMPLETE CHANGE ALL THIS CODE
// I repeat, this is a prototype
unsigned char* map_pix;
sf::Texture map_tex;
sf::Sprite map_sprite;

unsigned char* cc_pix;
sf::Texture cc_tex;
sf::Sprite cc_sprite;
sf::Font font;
sf::Text text;

Renderer::Renderer() {
    if (!font.loadFromFile("../resources/gamefont.tff"))
        std::cout << "Couldn't load font\n";
    text.setFont(font);
    text.setCharacterSize(24);
    map_pix = new unsigned char[21*21*4];
    cc_pix = new unsigned char[1*1*4];
    map_tex.create(21, 21);
    map_sprite.setTexture(map_tex, true);
    map_sprite.setScale(sf::Vector2f(16.0f, 16.0f));
    map_sprite.setPosition(sf::Vector2f(0.f, 0.f));

    cc_tex.create(1, 1);
    cc_sprite.setTexture(cc_tex, true);
    cc_sprite.setScale(sf::Vector2f(16.0f, 16.0f));
    cc_pix[0] = 255;
    cc_pix[1] = 255;
    cc_pix[2] = 255;
    cc_pix[3] = 255;
    cc_tex.update(cc_pix);
}
Renderer::~Renderer() {}

std::string options[5] = {"Press Space", "Option1", "Option2", "Option3", "Option4"}; 
void Renderer::render(sf::RenderWindow &window, GameState &state)
{

    window.clear(sf::Color::Black);

    // TODO: Proper mode handling, put each in a function
    if (state.mode == 0)
    {
        if (state.option == 0)
        {
            
        }
        else if (state.option == 1)
        {
        }
        text.setColor(sf::Color::White);
        
        for (int i = 0; i < 5; ++i)
        {
            int cr = state.option == i;
            text.setString(options[i]);
            text.setCharacterSize(24 + (cr ? 3 : 0));
            text.setPosition(
                50 + (cr ? 5 : 0),
                50 + (cr ? -2 : 0) + (i * 30)
            );
            window.draw(text);
        }
    }
    else if (state.mode == 1)
    {
        // put the legit version of this in "rendergame()" or something
        // TODO: remove prototype graphics    
        for (int i = 0; i < 21; ++i)
        {
            for (int j = 0; j < 21; ++j)
            {
                map_pix[(i * 21 + j)*4+0] = state.getTile(i, j) * 80;
                map_pix[(i * 21 + j)*4+1] = state.getTile(i, j) * 80;
                map_pix[(i * 21 + j)*4+2] = state.getTile(i, j) * 80;
                map_pix[(i * 21 + j)*4+3] = 255;
            }
        }
        map_tex.update(map_pix);
        window.draw(map_sprite);
        cc_sprite.setPosition(sf::Vector2f((state.pos.x)*16, (state.pos.y)*16));
        window.draw(cc_sprite);
        for (const Bomb& bomb : state.bombs) {
            if ((fmod(bomb.tick, 0.4)) > 0.2 == 0) {
                cc_sprite.setPosition(sf::Vector2f(bomb.x*16, bomb.y*16));
                window.draw(cc_sprite);
            }
            if (bomb.tick > 2.5) {
                cc_sprite.setPosition(sf::Vector2f(bomb.x*16, bomb.y*16));
                window.draw(cc_sprite);
                cc_sprite.setPosition(sf::Vector2f((bomb.x-1)*16, (bomb.y  )*16));
                window.draw(cc_sprite);
                cc_sprite.setPosition(sf::Vector2f((bomb.x+1)*16, (bomb.y  )*16));
                window.draw(cc_sprite);
                cc_sprite.setPosition(sf::Vector2f((bomb.x  )*16, (bomb.y+1)*16));
                window.draw(cc_sprite);
                cc_sprite.setPosition(sf::Vector2f((bomb.x  )*16, (bomb.y-1)*16));
                window.draw(cc_sprite);
            }
        }
    }

    window.display();


	//std::cout << "Rendering..." << std::endl;
}

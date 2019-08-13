#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "Bomberman!");
    sf::Texture texture;
    if (!texture.loadFromFile("../textures/pine-wood.jpg"))
    {
    }
    texture.setSmooth(true);

    while (window.isOpen())
    {
        texture.setRepeated(true);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sf::CircleShape shape(50.f);
        window.draw(sprite);
        window.draw(shape);

        window.display();
    }

    return 0;
}
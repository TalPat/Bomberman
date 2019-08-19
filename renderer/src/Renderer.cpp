#include "../include/Renderer.hpp"

#include <iostream>
#include <cmath>

const float SCALE = 30;

void Renderer::render(sf::RenderWindow &window, const GameState &state)
{
	window.clear(sf::Color::Black);
	map(window, state);
	bombs(window, state);
	player(window, state);
	window.display();
}

void Renderer::bombs(sf::RenderWindow &window, const GameState &state)
{

	// position.y *= -1;

	sf::CircleShape circle(SCALE / 2);
	circle.setFillColor(sf::Color(250, 20, 50));
	
    std::list<Bomb> bombs = state.bombs.bomb_list;
    std::list<Bomb>::iterator  i = bombs.begin();
    while (i != bombs.end())
    {
		sf::Vector2i position((*i).position);
		circle.setPosition((*i).position.x * SCALE,
			(*i).position.y * SCALE);
		if ((fmod((*i).tick, 0.4)) > 0.2)
			window.draw(circle);	
        i++;
    }

}

void Renderer::player(sf::RenderWindow &window, const GameState &state)
{
	sf::CircleShape player(SCALE / 2);

	sf::Vector2f playerPosition(state.player.position());
	playerPosition -= sf::Vector2f(0.5, 0.5);
	// playerPosition.y *= -1;
	playerPosition *= SCALE;

	player.setPosition(playerPosition);
	player.setFillColor(sf::Color(250, 20, 50));
	window.draw(player);
}

void Renderer::map(sf::RenderWindow &window, const GameState &state)
{
	const Map &map = state.map;
	const sf::Vector2i &mapSize = map.size();
	Tile tile;
	sf::RectangleShape cell(sf::Vector2f(SCALE, SCALE));
	for (int y = 0; y < mapSize.y; y++)
	{
		for (int x = 0; x < mapSize.x; x++)
		{
			sf::Vector2i cellPosition(x, y);
			tile = map.tileAt(cellPosition);
			if (tile != Tile::Clear)
			{
				cellPosition *= static_cast<int>(SCALE);
				cell.setPosition(cellPosition.x, cellPosition.y);
				switch (tile)
				{
				case Tile::Solid:
					cell.setFillColor(sf::Color(50, 150, 20));
					break;
				case Tile::Destructible:
					cell.setFillColor(sf::Color(50, 50, 150));
					break;
				default:
					break;
				}
				window.draw(cell);
			}
		}
	}
}
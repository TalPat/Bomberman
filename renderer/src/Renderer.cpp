#include "../include/Renderer.hpp"

#include <iostream>

const float SCALE = 30;

void Renderer::render(sf::RenderWindow &window, const GameState &state)
{
	window.clear(sf::Color::Black);
	map(window, state);
	player(window, state);
	window.display();
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
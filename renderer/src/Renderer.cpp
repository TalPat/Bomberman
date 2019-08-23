#include "../include/Renderer.hpp"

#include <iostream>

const float SCALE = 30;

void Renderer::render(sf::RenderWindow &window, const GameState &state)
{
	window.clear(sf::Color::Black);
	map(window, state);
	player(window, state);
	enemyList(window, state);
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

void Renderer::enemyList(sf::RenderWindow &window, const GameState &state)
{
	for(auto &e: state.eList.eList){
		enemy(window, state,*e);
	}
}

void Renderer::enemy(sf::RenderWindow &window, const GameState &state,const Enemy &e)
{
	sf::CircleShape enemy(SCALE / 2);

	sf::Vector2f enemyPosition(e.position());
	enemyPosition -= sf::Vector2f(0.5, 0.5);
	enemyPosition *= SCALE;

	enemy.setPosition(enemyPosition);
	switch(e.type){
		case EnemyType::EBallom:
			enemy.setFillColor(sf::Color(0, 255, 255));
			break;
		case EnemyType::EAggroBallom:
			enemy.setFillColor(sf::Color(255, 102, 178));
			break;
		default:
			enemy.setFillColor(sf::Color(255, 255, 0));
			break;
	}
	window.draw(enemy);
}

void Renderer::map(sf::RenderWindow &window, const GameState &state)
{
	const Map &map = state.map;
	const sf::Vector2i &mapSize = map.size();
	Tile tile;
	sf::RectangleShape cell(sf::Vector2f(SCALE, SCALE));
	sf::CircleShape bomb(SCALE / 2);
	cell.setFillColor(sf::Color(250));

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
					window.draw(cell);
					break;
				case Tile::Destructible:
					cell.setFillColor(sf::Color(50, 50, 150));
					window.draw(cell);
					break;
				case Tile::Bomb:
					bomb.setPosition(cellPosition.x, cellPosition.y);
					window.draw(bomb);
					break;
				case Tile::Flame:
					cell.setFillColor(sf::Color(255, 0, 0));
					window.draw(cell);
					break;
				default:
					break;
				}
			}
		}
	}
}

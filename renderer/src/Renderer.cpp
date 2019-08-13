#include "../include/Renderer.hpp"

#include <iostream>

const float SCALE = 10;

void Renderer::render(sf::RenderWindow &window, const GameState &state)
{
	window.clear(sf::Color::Black);

	sf::CircleShape player(SCALE / 2);

	sf::Vector2f playerPosition(state.player.position());
	playerPosition.y *= -1;
	playerPosition *= SCALE;

	player.move(playerPosition);
	player.setFillColor(sf::Color(100, 250, 50));
	window.draw(player);

	window.display();
}

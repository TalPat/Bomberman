#include "../include/Renderer.hpp"

#include <iostream>

const float SCALE = 10;

void Renderer::render(sf::RenderWindow &window, const GameState &state)
{
	std::cout << "Rendering..." << std::endl;

	//Clear previous frame
	window.clear(sf::Color::Black);

	sf::CircleShape player(SCALE / 2);
	sf::Transform position;
	position.translate(state.player.position());

	player.setFillColor(sf::Color(100, 250, 50));
	window.draw(player);

	window.display();
}

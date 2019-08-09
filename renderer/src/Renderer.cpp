#include "../include/Renderer.hpp"

#include <iostream>

void Renderer::render(sf::RenderWindow &window, const std::vector<IRenderable *> renderables)
{
	std::cout << "Rendering..." << std::endl;

	//Clear previous frame
	window.clear(sf::Color::Black);

	for (auto renderable : renderables)
	{
		renderable->render(window);
	}

	window.display();
}

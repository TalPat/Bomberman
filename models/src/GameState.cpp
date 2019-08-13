#include "../include/GameState.hpp"

GameState::GameState(int width, int height)
	: width(width),
	  height(height),
	  map(width * height, Tile::Clear)
{
	this->playerPos = sf::Vector2f(0.5, 0.5);

	// for (int i = 0; i < height; i++)
	// {
	// 	for (int j = 0; j < width; j++)
	// 	{
	// 		if (i == 0 || i == game.width - 1 || j == 0 || j == game.height - 1)
	// 		{
	// 			// game.setTile(i, j, 1); // border
	// 			this->map[j * height + i] = Tile::Border;
	// 		}
	// 		else if (i % 2 == 0 && j % 2 == 0)
	// 		{
	// 			// game.setTile(i, j, 1); // solid walls
	// 			this->map[j * height + i] = Tile::Solid;
	// 		}
	// 		else
	// 		{
	// 			// game.setTile(i, j, 0); // clear
	// 			if (rand() % 5 == 0 && (i > 3 || j > 3))
	// 			{
	// 				this->map[j * height + i] = Tile::Destructible;
	// 			}
	// 			else
	// 			{
	// 				this->map[j * height + i] = Tile::Clear;
	// 			}
	// 		}
	// 	}
	// }
}

GameState::~GameState()
{
}

// void GameState::movePlayer(bool *keys, float dd)
// {
// 	if (keys[EngineEvent::LEFT] && !getTile(pos.y + 0.5, pos.x + 0.2 - dd))
// 		pos.x -= dd;
// 	if (keys[EngineEvent::RIGHT] && !getTile(pos.y + 0.5, pos.x + 0.8 + dd))
// 		pos.x += dd;
// 	if (keys[EngineEvent::UP] && !getTile(pos.y + 0.2 - dd, pos.x + 0.5))
// 		pos.y -= dd;
// 	if (keys[EngineEvent::DOWN] && !getTile(pos.y + 0.8 + dd, pos.x + 0.5))
// 		pos.y += dd;
// }

// Bombs
// void GameState::tickBombs(float dt)
// {
// 	std::list<Bomb>::iterator i = bombs.begin();
// 	while (i != bombs.end())
// 	{
// 		(*i).tick += dt; // update bomb tick with game deltatime
// 		// When bomb reaches end of life, remove walls, remove bomb from bomb list
// 		if ((*i).tick > 2.6)
// 		{
// 			explodeBomb((*i).x, (*i).y, 1);
// 			// last parameter here is size ^^
// 			// should be changed based in powerup or something later
// 			bombs.erase(i++);
// 		}
// 		else
// 			i++;
// 	}
// }

// void GameState::placeBomb()
// {
// 	// place bomb at current player position
// 	Bomb new_bomb = {
// 		.x = (int)(pos.x + 0.5),
// 		.y = (int)(pos.y + 0.5),
// 		.tick = 0};
// 	bombs.push_back(new_bomb);
// }
// void explodeBomb(float x, float y, int size)
// {
// 	for (int i = 0; i < size; ++i)
// 	{
// 		if (getTile(y + i, x) == 2)
// 			setTile(y + i, x, 0);
// 		if (getTile(y - i, x) == 2)
// 			setTile(y - i, x, 0);
// 		if (getTile(y, x - i) == 2)
// 			setTile(y, x - i, 0);
// 		if (getTile(y, x + i) == 2)
// 			setTile(y, x + i, 0);
// 	}
// }

// Map
// int width;
// int height;
// int *walls;

// int getTile(int x_coord, int y_coord)
// {
// 	return this->walls[y_coord * width + x_coord];
// }

// void setTile(int x_coord, int y_coord, int val)
// {
// 	this->walls[y_coord * width + x_coord] = val;
// }

#include "../include/Enemies.hpp"
// #include <thread>
Enemies::Enemies()
{
	populate(100);
}

Enemies::~Enemies()
{
	for(auto &e:this->list)
		delete e;
}
void Enemies::updateAll(float deltaTime, const Map &map, const Player &player)
{
	for(auto &e:this->list)
	{
		// std::thread t1(std::ref(e->update), std::ref(deltaTime), std::ref(map), std::ref(player));
		e->update(deltaTime, map, player);
		// t1.join();
	}
}

void Enemies::populate()
{
	//Used for testing new Enemies
	IEnemy *e =new IEnemy();
	Ballom *b = new Ballom();
	list.push_back(e);
	list.push_back(b);
}
// void Enemies::populate(int numEnemies,int level, const Map &map){

// }
void Enemies::populate(int numEnemies)
{
	srand(time(NULL));
	int enemyType;
	IEnemy *e;
	for(int i = 0; i < numEnemies;i++)
	{
		enemyType = (rand() % 3);
		switch (enemyType)
		{
			case 0:
				e = new Ballom();
				break;
			case 1:
				e = new Finder();
				break;
			default:
				// e = new Finder();
				e = new IEnemy();
				break;
		}
		list.push_back(e);
	}
}

void Enemies::kill(const Map &map)
{
	auto comp = [](Tile tile) {
		return tile == Tile::Flame;
	};
	std::list<IEnemy*> enemiesToKill;
	for(auto &e:this->list)
	{
		if (map.collide(e->position(), 0.49, comp))
			enemiesToKill.push_back(e);
	}
	for(auto &e:enemiesToKill)
	{
		delete e;
		list.remove(e);
	}
	enemiesToKill.clear();
}
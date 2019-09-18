#include "../include/Enemies.hpp"

Enemies::Enemies()
{
}

Enemies::~Enemies()
{
	for(auto &e:this->list)
		delete e;
}

void Enemies::init(int level)
{
	populate(5);
}

void Enemies::updateAll(float deltaTime, const Map &map)
{
	for(auto &e:this->list)
	{
		e->update(deltaTime, map);
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

void Enemies::populate(int numEnemies)
{
	int enemyType;
	IEnemy *e;
	for(int i = 0; i < numEnemies;i++)
	{
		enemyType = (rand() % 2);
		switch (enemyType)
		{
			case 0:
				e = new Ballom();
				break;
		
			default:
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
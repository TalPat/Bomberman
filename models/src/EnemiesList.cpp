#include "../include/Enemies.hpp"
#include <iostream>
		Enemies::Enemies(){
			populate(5);
		}
		Enemies::~Enemies(){
			for(auto &e:this->list)
				delete e;
		}
		void Enemies::updateAll(float deltaTime, const Map &map){
			for(auto &e:this->list){
				e->update(deltaTime, map);
			}
		}
		
		void Enemies::populate(){			//Used for testing new Enemies
			IEnemy *e =new IEnemy();
			Ballom *b = new Ballom();
			list.push_back(e);
			list.push_back(b);
		}
		void Enemies::populate(int numEnemies){
			int enemyType;
			IEnemy *e;
			for(int i = 0; i < numEnemies;i++){
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
		// UNTESTED
		void Enemies::kill(sf::Vector2i killPosition){
			std::list<IEnemy*> enemiesToKill;
			for(auto &e:this->list){
				if(sf::Vector2i(e->position()) == killPosition)
					enemiesToKill.push_back(e);
			}
			for(auto &e:enemiesToKill){
				delete e;
				list.remove(e);
			}
			enemiesToKill.clear();
		}


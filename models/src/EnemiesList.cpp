#include "../include/EnemiesList.hpp"
#include <iostream>
		EnemiesList::EnemiesList(){
			populate(2);
		}
		EnemiesList::~EnemiesList(){
			for(auto &e:this->eList)
				delete e;
		}
		void EnemiesList::updateAll(float deltaTime, const Map &map){
			for(auto &e:this->eList){
				e->update(deltaTime, map);
			}
		}
		
		void EnemiesList::populate(){			//Used for testing new Enemies
			Enemy *e =new Enemy();
			Ballom *b = new Ballom();
			eList.push_back(e);
			eList.push_back(b);
		}
		void EnemiesList::populate(int numEnemies){
			int enemyType;
			Enemy *e;
			for(int i = 0; i < numEnemies;i++){
				enemyType = (rand() % 2);
				switch (enemyType)
				{
					case 0:
						e = new Ballom();
						break;
				
					default:
						e = new Enemy();
						break;
				}
				eList.push_back(e);
			}
		}


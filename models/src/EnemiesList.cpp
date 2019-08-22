#include "../include/EnemiesList.hpp"
#include <iostream>
		EnemiesList::EnemiesList(){
			populate();
		}
		EnemiesList::~EnemiesList(){
			for(auto &e:this->eList)
				e.~Enemy();
		}
		void EnemiesList::updateAll(float deltaTime, const Map &map){
			for(auto &e:this->eList){
				e.update(deltaTime, map);
			}
		}
		void EnemiesList::populate(){
			Enemy e;
			Ballom b;
			eList.push_back(e);
			eList.push_back(b);
			for (auto &e:eList)
				std::cout << "Enemy added to list\n";
		}


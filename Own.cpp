#include "Map.hpp"
#include <iostream>
#include <ctime>
#include <SFML/System.hpp>
enum EnemyMoveState
{
	north,
	east,
	south,
	west
};
EnemyMoveState calculatedirection(sf::Vector2i start, sf::Vector2i end){
    int dy = start.y - end.y;
    int dx = start.x - end.x;
    std::cout << "dx ==> " << dx << "\n";
    std::cout << "dy ==> " << dy << "\n";
    if(!dy)
        return (dx > 0 ? EnemyMoveState::west:EnemyMoveState::east);
    else if (!dx)
        return (dy > 0 ? EnemyMoveState::north:EnemyMoveState::south );
    else if(abs(dy) <= abs(dx))
        return (dy >= 0 ? EnemyMoveState::north:EnemyMoveState::south );
    else/* if(abs(dx) > abs(dy))*/
        return (dx >= 0 ? EnemyMoveState::west:EnemyMoveState::east);
    /*else
        return EnemyMoveState::none;
    */
    
}
sf::Vector2i findpath(Map map, sf::Vector2i start, sf::Vector2i end){
    // sf::Vector2i estblock(start.x, start.y);
    sf::Vector2i path(start.x,start.y);
        // findpath(map, start, end);
        switch (calculatedirection(start, end))
        {
        case EnemyMoveState::north:
            path.y -= 1;
            std::cout << "North"<<"\n";
            break;
        case EnemyMoveState::south:
            path.y += 1;
            std::cout << "South"<<"\n";
            break;
        case EnemyMoveState::west:
            path.x -= 1;
            std::cout << "West"<<"\n";
            break;
        case EnemyMoveState::east:
            path.x += 1;
            std::cout << "East"<<"\n";
            break;
        default:
            break;
        }
        if(map.tileAt(path) == Tile::Solid || map.tileAt(path) == Tile::Destructible || map.tileAt(path) == Tile::Bomb)
            return start;
    return path;
}
void printmap(Map map,sf::Vector2i start,sf::Vector2i end, sf::Vector2i path){
    for(int y =0;y< map.size().y;y++){
            for(int x =0;x< map.size().x;x++){
                if(x == start.x && y == start.y)
                    std::cout <<FCYAN<<BCYAN<< "E"<<RESET;
                else if(x == end.x && y == end.y)
                    std::cout <<FYELLOW<<BYELLOW<< "P"<<RESET;
                else if(x ==path.x && y == path.y)
                    std::cout <<FGREEN<<BGREEN<< "R"<<RESET;
                else if(map.tileAt(sf::Vector2i(x, y)) == Tile::Solid)
                    std::cout <<FRED<<BRED<< "W"<<RESET;
                else if(map.tileAt(sf::Vector2i(x, y)) == Tile::Destructible)
                    std::cout <<FRED<<BRED<< "W"<<RESET;
                else
                    std::cout << ".";
            }
            std::cout << "\n";
        }
}
void followpath(sf::Vector2i start,sf::Vector2i path){
    start = path;
}
int main(int ac, char *av[]){
    int maph = atoi(av[1]);
    int mapv = atoi(av[2]);
    srand(time(NULL));
    int startx, starty, endx, endy;  
	do{
		startx = (rand()%(maph-2))+1; 
		starty = (rand()%(mapv-2))+1;
	}while(!((startx%2) && (starty%2)));

	do{
		endx = (rand()%(maph -2))+1; 
		endy = (rand()%(mapv -2))+1;
	}while(!((endx%2) && (endy%2)));

	sf::Vector2i start(startx,starty);
	sf::Vector2i end(endx,endy);

        Map map(maph,mapv);
        // sf::Vector2i path = findpath(map, start, end);
        while(start != end){
            sf::Vector2i path = findpath(map, start, end);
            printmap(map,start, end, path);
            getchar();
            start = path;
            // followpath(start, path);
        }
}
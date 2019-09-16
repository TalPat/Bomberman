#ifndef MAP_HPP
#define MAP_HPP
#define FBLACK "\033[1;30m" 
#define FRED "\033[1;31m" 
#define FGREEN "\033[1;32m" 
#define FYELLOW "\033[1;33m" 
#define FBLUE "\033[1;34m" 
#define FMAGENTA "\033[1;35m" 
#define FCYAN "\033[1;36m" 
#define FWHITE "\033[1;37m"

#define BBLACK "\033[1;40m" 
#define BRED "\033[1;41m" 
#define BGREEN "\033[1;42m" 
#define BYELLOW "\033[1;43m" 
#define BBLUE "\033[1;44m" 
#define BMAGENTA "\033[1;45m" 
#define BCYAN "\033[1;46m" 
#define BWHITE "\033[1;47m" 

#define RESET "\033[0m"
// #include <SFML/System.hpp>

#include <vector>
#include <SFML/System.hpp>
enum Tile
{
	Solid,
	Clear,
	Destructible,
	Bomb,
	Flame,
};

// class Coordinate
// {
// public:
// 	int x;
// 	int y;
// 	Coordinate (int x, int y){
// 		this->x = x;
// 		this->y = y;
// 	};
// 	~Coordinate(){
// 		return ;
// 	};
// };
class Map
{
private:
	sf::Vector2i _size;
	std::vector<Tile> _tiles;

public:
	Map();
	Map(int x, int y);
	~Map();

	Tile tileAt(sf::Vector2i pos) const;
	void setTile(sf::Vector2i pos, Tile tile);
	const sf::Vector2i &size() const;
};

#endif
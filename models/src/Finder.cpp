#include "../include/Finder.hpp"
#include <iostream>
const int NUM_MOVEMENT_STATES = 4;
const float AGGROTIME = 4;
const float DEFAULT_SPEED = 2.5;
const float AUTOSWITCH = 1;
const sf::Vector2f DEFAULT_START(9.5, 9.5);

Finder::Finder()		
{
	_position = (DEFAULT_START);
	_enemySpeed = (DEFAULT_SPEED);
	moveState = (EnemyMoveState::north);
	_switchTime = (AUTOSWITCH);
	type = (EnemyType::EFinder);
	_wallPass = (true);
	changeMoveState();
}

Finder::Finder(sf::Vector2f start)		
{
	_position = (start);
	_enemySpeed = (DEFAULT_SPEED);
	moveState = (EnemyMoveState::north);
	_switchTime = (AUTOSWITCH);
	type = (EnemyType::EFinder);
	_wallPass = (true);
	changeMoveState();
}

Finder::~Finder(){
	return;
}

void Finder::changeMoveState()
{
	this->moveState =(EnemyMoveState)(rand() % (NUM_MOVEMENT_STATES));
}
void Finder::changeMoveState(const Map &map, const Player &player){
	// this->moveState = update_path(map, )
	this->moveState = update_path(map, sf::Vector2i(this->position()), sf::Vector2i(player.position()));

	// this->moveState = findpath(map, sf::Vector2i(this->position()), sf::Vector2i(player.position()));
}

void Finder::update(float deltaTime, const Map &map, const Player &player)
{
	_switchTime -= deltaTime;
	// _aggression -= deltaTime;
	// if(_aggression <= 0)
	// {
		// this->changeAggression();
	// }
	if((int)(this->position().x)%2 || (int)(this->position().y)%2)
			_switchTime = 0;
	if(_switchTime <= 0)
	{
		this->changeMoveState(map, player);
		// switch (this->moveState)
		// {
		// case EnemyMoveState::north:
		// 	std::cout << "N\n";
		// 	break;
		// case EnemyMoveState::south:
		// 	std::cout << "S\n";
		// 	break;
		// case EnemyMoveState::east:
		// 	std::cout << "E\n";
		// 	break;
		// case EnemyMoveState::west:
		// 	std::cout << "W\n";
		// 	break;
		// default:
		// 	break;
		// }
		// if(_aggression)
		// 	_switchTime = (rand() % (int)(AUTOSWITCH/2)) + 1;
		// else
		
			_switchTime = (rand() % (int)(AUTOSWITCH)) +1 ;
	}
	this->move(deltaTime, map);
}

void Finder::changeAggression()
{
	// _aggression = (rand() % 4);
	if(_aggression == 3 && type == EnemyType::EBallom)
	{
		_enemySpeed = DEFAULT_SPEED + 1.5;
		type = EnemyType::EAggroBallom;
	}
	else
	{
		_enemySpeed = DEFAULT_SPEED;
		type = EnemyType::EBallom;
	}
		_aggression = AGGROTIME;		
}

EnemyMoveState Finder::calculatedirection(sf::Vector2i start, sf::Vector2i end){
    int dy = start.y - end.y;
    int dx = start.x - end.x;
    // std::cout << "dx ==> " << dx << "\n";
    // std::cout << "dy ==> " << dy << "\n";
	if(start.x%2 == 0)
		dy = 0;
	else if(start.y%2 == 0)
		dx = 0;
	
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
EnemyMoveState Finder::findpath(Map map, sf::Vector2i start, sf::Vector2i end){
    // sf::Vector2i estblock(start.x, start.y);
	EnemyMoveState estDir = calculatedirection(start, end);
    sf::Vector2i path(start.x,start.y);
        // findpath(map, start, end);
        switch (estDir)
        {
        case EnemyMoveState::north:
            path.y -= 1;
            // std::cout << "North"<<"\n";
            break;
        case EnemyMoveState::south:
            path.y += 1;
            // std::cout << "South"<<"\n";
            break;
        case EnemyMoveState::west:
            path.x -= 1;
            // std::cout << "West"<<"\n";
            break;
        case EnemyMoveState::east:
            path.x += 1;
            // std::cout << "East"<<"\n";
            break;
        default:
            break;
        }
        if(map.tileAt(path) == Tile::Solid || (!_wallPass && map.tileAt(path) == Tile::Destructible) || (!_wallPass && map.tileAt(path) == Tile::Bomb))
            return (EnemyMoveState)(rand() % (NUM_MOVEMENT_STATES));
    return estDir;
}
















// #include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>
// #include "Map.hpp"

#define FBLACK "\u001b[1;30m" 
#define FRED "\033[1;31m" 
#define FGREEN "\033[1;32m" 
#define FYELLOW "\033[1;33m" 
#define FBLUE "\033[1;34m" 
#define FMAGENTA "\033[1;35m" 
#define FCYAN "\033[1;36m" 
#define FWHITE "\033[1;37m"
#define TOP "\u001b[0;0H"
#define BBLACK "\033[1;40m" 
#define BRED "\033[1;41m" 
#define BGREEN "\033[1;42m" 
#define BYELLOW "\033[1;43m" 
#define BBLUE "\033[1;44m" 
#define BMAGENTA "\033[1;45m" 
#define BCYAN "\033[1;46m" 
#define BWHITE "\033[1;47m" 

#define RESET "\033[0m"

using namespace std;


// const int n=21; // horizontal size of the map
// const int m=21; // vertical size size of the map
//  int map[n][m];
//  int closed_nodes_map[n][m]; // map of closed (tried-out) nodes
//  int open_nodes_map[n][m]; // map of open (not-yet-tried) nodes
//  int dir_map[n][m]; // map of directions
const int dir=4; // number of possible directions to go at any position
// if dir==4
 int dx[dir]={1, 0, -1, 0};
 int dy[dir]={0, 1, 0, -1};
// if dir==8
// static int dx[dir]={1, 1, 0, -1, -1, -1, 0, 1};
// static int dy[dir]={0, 1, 1, 1, 0, -1, -1, -1};

class node
{
	// current position
	int xPos;
	int yPos;
	// total distance already travelled to reach the node
	int level;
	// priority=level+remaining distance estimate
	int priority;  // smaller: higher priority

	public:
		node(sf::Vector2i start, int d, int p) 
			{xPos=start.x; yPos=start.y; level=d; priority=p;}
	
		int getxPos() const {return xPos;}
		int getyPos() const {return yPos;}
		int getLevel() const {return level;}
		int getPriority() const {return priority;}

		void updatePriority(const sf::Vector2i &end)
		{
			 priority=level+estimate(end)*10; //A*
		}

		// give better priority to going strait instead of diagonally
		void nextLevel(const int & i) // i: direction
		{
			 level+=(dir==8?(i%2==0?10:14):10);
		}
		
		// Estimation function for the remaining distance to the goal.
		const int & estimate(const sf::Vector2i & point) const
		{
			static int xd, yd, d;
			xd=point.x-xPos;
			yd=point.y-yPos;         

			// Euclidian Distance
			// d=static_cast<int>(sqrt(xd*xd+yd*yd));

			// Manhattan distance
			d=abs(xd)+abs(yd);
			
			// Chebyshev distance
			//d=max(abs(xd), abs(yd));

			return(d);
		}
};

// Determine priority (in the priority queue)
bool operator<(const node & a, const node & b)
{
  return a.getPriority() > b.getPriority();
}

// A-star algorithm.
// The route returned is a string of direction                   digits.
string pathFind(const Map &mapeth,int map[][21],const sf::Vector2i & start, const sf::Vector2i & end )
{
	int m = mapeth.size().y;
	int n = mapeth.size().x;
	 int closed_nodes_map[n][m]; // map of closed (tried-out) nodes
 	 int open_nodes_map[n][m]; // map of open (not-yet-tried) nodes
	 int dir_map[n][m]; 
	static priority_queue<node> pq[2]; // list of open (not-yet-tried) nodes
	static int pqi; // pq index
	// static node n0;
	// static node m0;
	static int i, j, x, y, xdx, ydy;
	static char c;
	pqi=0;

	// reset the node maps
	for(y=0;y<m;y++)
	{
		for(x=0;x<n;x++)
		{
			closed_nodes_map[x][y]=0;
			open_nodes_map[x][y]=0;
		}
	}

	// create the start node and push into list of open nodes
	node n0(start, 0, 0);
	n0.updatePriority(end);
	pq[pqi].push(n0);
	open_nodes_map[x][y]=n0.getPriority(); // mark it on the open nodes map

	// A* search
	while(!pq[pqi].empty())
	{
		// get the current node w/ the highest priority
		// from the list of open nodes
		n0=node(sf::Vector2i(pq[pqi].top().getxPos(), pq[pqi].top().getyPos()), pq[pqi].top().getLevel(), pq[pqi].top().getPriority());

		x=n0.getxPos(); y=n0.getyPos();

		pq[pqi].pop(); // remove the node from the open list
		open_nodes_map[x][y]=0;
		// mark it on the closed nodes map
		closed_nodes_map[x][y]=1;

		// quit searching when the goal state is reached
		//if((*n0).estimate(xFinish, yFinish) == 0)
		if(x==end.x && y==end.y) 
		{
			// generate the path from finish to start
			// by following the directions
			string path="";
			while(!(x==start.x && y==start.y))
			{
				j=dir_map[x][y];
				c='0'+(j+dir/2)%dir;
				path=c+path;
				x+=dx[j];
				y+=dy[j];
			}

			// garbage collection
			// delete n0;
			// empty the leftover nodes
			while(!pq[pqi].empty()) pq[pqi].pop();           
			return path;
		}

		// generate moves (child nodes) in all possible directions
		for(i=0;i<dir;i++)
		{
			xdx=x+dx[i]; ydy=y+dy[i];

			if(!(xdx<0 || xdx>n-1 || ydy<0 || ydy>m-1 || map[xdx][ydy]==1 
				|| closed_nodes_map[xdx][ydy]==1))
			{
				// generate a child node
				node m0( sf::Vector2i(xdx, ydy), n0.getLevel(), 
							 n0.getPriority());
				m0.nextLevel(i);
				m0.updatePriority(end);

				// if it is not in the open list then add into that
				if(open_nodes_map[xdx][ydy]==0)
				{
					open_nodes_map[xdx][ydy]=m0.getPriority();
					pq[pqi].push(m0);
					// mark its parent node direction
					dir_map[xdx][ydy]=(i+dir/2)%dir;
				}
				else if(open_nodes_map[xdx][ydy]>m0.getPriority())
				{
					// update the priority info
					open_nodes_map[xdx][ydy]=m0.getPriority();
					// update the parent direction info
					dir_map[xdx][ydy]=(i+dir/2)%dir;

					// replace the node
					// by emptying one pq to the other one
					// except the node to be replaced will be ignored
					// and the new node will be pushed in instead
					while(!(pq[pqi].top().getxPos()==xdx && 
						   pq[pqi].top().getyPos()==ydy))
					{                
						pq[1-pqi].push(pq[pqi].top());
						pq[pqi].pop();       
					}
					pq[pqi].pop(); // remove the wanted node
					
					// empty the larger size pq to the smaller one
					if(pq[pqi].size()>pq[1-pqi].size()) pqi=1-pqi;
					while(!pq[pqi].empty())
					{                
						pq[1-pqi].push(pq[pqi].top());
						pq[pqi].pop();       
					}
					pqi=1-pqi;
					pq[pqi].push(m0); // add the better node instead
				}
				// else delete m0; // garbage collection
			}
		}
		// delete n0; // garbage collection
	}
	return ""; // no route found
}
EnemyMoveState Finder::update_path(const Map &mapeth, sf::Vector2i start, sf::Vector2i end){
	// int m = mapeth.size().y;
	// int n = mapeth.size().x;
	int map[21][21];
	// int map[][];
	// **map =(int)malloc(sizeof(int)*mapeth.size().x);
	EnemyMoveState direction;
	Tile tile;
	for (int y = 0; y < mapeth.size().y; y++)
	{
		for (int x = 0; x < mapeth.size().x; x++)
		{
			sf::Vector2i cellPosition(x, y);
			tile = mapeth.tileAt(cellPosition);
			if (tile != Tile::Clear)
			{
				switch (tile)
				{
				case Tile::Solid:
					map[x][y] = 1;
					break;
				case Tile::Destructible:
					map[x][y] = 1;
					break;
				case Tile::Bomb:
					map[x][y] = 1;
					break;
				case Tile::Flame:
					map[x][y] = 1;
					break;
				default:
					break;
				}
			}
		}
	}

	// sf::Vector2i start(19,19);
	// sf::Vector2i end(1,1);
	// cout<<"Map Size (X,Y): "<<n<<","<<m<<endl;
	// cout<<"Start: "<<start.x<<","<<start.y<<endl;
	// cout<<"Finish: "<<end.x<<","<<end.y<<endl;
	
	// get the route
	// clock_t clockstart = clock();
	string route=pathFind(mapeth,map,start, end);
	// if(route=="") cout<<"An empty route generated!"<<endl;
	// clock_t clockend = clock();
	// double time_elapsed = double(clockend - clockstart);
	// cout<<"Time to calculate the route (ms): "<<time_elapsed<<endl;
	// cout<<"Route:"<<endl;
	// cout<<route<<endl<<endl;

	// follow the route on the map and display it 
	// if(route.length()>0)
	// {
		int j; char c;
		sf::Vector2i point = start;
		map[point.x][point.y]=2;
		for(int i=0;i<route.length();i++)
		{
			c =route.at(i);
			j=atoi(&c); 
			point.x+=dx[j];
			point.y+=dy[j];
			map[point.x][point.y]=3;
		}
		map[end.x][end.y]=4;
	
		// display the map with the route
		
	// }
	// cout << TOP;
	for(int y=0;y<mapeth.size().y;y++)
	{
		for(int x=0;x<mapeth.size().x;x++)
			switch(map[x][y]){
				// case 0:		//empty
				// 	cout<< BBLACK <<FBLACK << "."<<RESET;
				// 	break;
				// case 1:	//obstacle
				// 	cout<< BRED <<FRED << "O"<<RESET;
				// 	break;
				case 2:	//start
					if		(map[x + 1][y] == 3)
						direction = EnemyMoveState::east;
					else if	(map[x - 1][y] == 3)
						direction = EnemyMoveState::west;
					else if	(map[x][y + 1] == 3)
						direction = EnemyMoveState::south;
					else if (map[x][y - 1] == 3)
						direction = EnemyMoveState::north;
					else
							direction = (EnemyMoveState)(rand() % (NUM_MOVEMENT_STATES));
					
					
				// 	cout<< BYELLOW <<FYELLOW << "S"<<RESET;
				// 	break;
				// case 3:	//routee
				// 	cout<< BGREEN <<FGREEN << "R"<<RESET;
				// 	break;
				// case 4:	//finish
				// 	cout<< BCYAN <<FCYAN << "F"<<RESET;
				// 	break;
				// default:
				// 	cout<< BBLACK <<FBLACK << "."<<RESET;
				// 	break;
		}
		// cout<<endl;
	}
	// free(map);
	// switch(direction)
	// {
	// 	case EnemyMoveState::north:cout << "N\n";break;
	// 	case EnemyMoveState::south:cout << "S\n";break;
	// 	case EnemyMoveState::east:cout << "E\n";break;
	// 	case EnemyMoveState::west:cout << "W\n";break;
	// 	default :break;
	// }
	return direction;
}
// int main()
// {
// 	// int n = atoi(argv[1]);
// 	// int m = atoi(argv[2]);

// 	srand(time(NULL));

// 	// create map
// 	Map *mapeth = new Map();
// 	int startx, starty, endx, endy;  
// 	do{
// 		startx = (rand()%19)+1; 
// 		starty = (rand()%19)+1;
// 	}while(!(startx%2) || !(starty%2));
// 	do{
// 		endx = (rand()%19)+1; 
// 		endy = (rand()%19)+1;
// 	}while(!(endx%2) || !(endy%2));
// 	sf::Vector2i start(startx,starty);
// 	sf::Vector2i end(endx,endy);
// 	EnemyMoveState est_dir;
// 	est_dir = update_path(*mapeth, start, end);
// 	switch(est_dir){
// 		case EnemyMoveState::north:
// 			std::cout <<  "North";
// 			break;
// 		case EnemyMoveState::south:
// 			std::cout <<  "South";
// 			break;
// 		case EnemyMoveState::east:
// 			std::cout <<  "East";
// 			break;
// 		case EnemyMoveState::west:
// 			std::cout <<  "West";
// 			break;
// 		default:
// 			std::cout <<  "None";
// 			break;
// 	}
// 	// getchar(); // wait for a (Enter) keypress  
// 	return(0);
// }


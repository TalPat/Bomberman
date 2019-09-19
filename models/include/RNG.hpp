#ifndef _RNG_HPP_
# define _RNG_HPP_
# include <random>
class RNG{
	public:
    static int getRandomNumber(int min,int max){
	// srand(time(NULL));
	// std::cout << "a : "<< a <<"\n";
	std::random_device rd;
	int randNum;
	std::uniform_int_distribution<int> dist(min, max);
	randNum = dist(rd);
	// std::cout << "number generated : " << randNum <<"\n";
	return randNum;
    }
};
#endif
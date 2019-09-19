#ifndef _RNG_HPP_
# define _RNG_HPP_
# include <random>
class RNG{
	public:
    static int getRandomNumber(int min,int max)
	{
		std::random_device rd;
		int randNum;
		std::uniform_int_distribution<int> dist(min, max);
		randNum = dist(rd);
		return randNum;
    }
};
#endif
#include "../include/RNG.hpp"

int RNG::getRandomNumber(int min,int max)
{
	std::random_device rd;
	int randNum;
	std::uniform_int_distribution<int> dist(min, max);
	// returns number between min and max (including max)
	randNum = dist(rd);
	return randNum;
}
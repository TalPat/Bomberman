
#include "./Bomberman.hpp"

int main()
{
	XInitThreads();
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	Bomberman bomberman;
	bomberman.setMutex(&mutex);

	bomberman.startGame();
}

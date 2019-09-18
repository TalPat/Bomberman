
#include "./Bomberman.hpp"

int main()
{
	#if !__APPLE__
		XInitThreads();
	#endif
	// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	Bomberman bomberman;
	// uncomment if object mutated by renderer
	// bomberman.setMutex(&mutex);

	bomberman.startGame();
}

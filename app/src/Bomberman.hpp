#ifndef _Bomberman_hpp_
#define _Bomberman_hpp_

#include "./AMainLoop.hpp"

#include <Engine.hpp>
#include <Renderer.hpp>
#include <vector>
#include <ctime>

class Bomberman : private AMainLoop
{

private:
	Engine engine;
	Renderer renderer;

	virtual void updateFunc();

public:
	Bomberman();
	~Bomberman();

	void startGame();
};

static timespec diff_ts(const timespec &t1, const timespec &t2);

#endif

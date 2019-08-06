#ifndef _AMainLoop_hpp_
#define _AMainLoop_hpp_

#include <vector>
#include <ctime>

class AMainLoop
{
private:
	const double frameRate = 60.0;
	timespec _perFrameTime = {0, 1 * 1000000000 / 60}; // Second to nano

	void loop();

	timespec _loopStart;
	timespec _loopEnd;
	timespec _sleep;
	timespec _diff;

	bool _running = false;

protected:
	virtual void updateFunc() = 0;

public:
	virtual ~AMainLoop() {}

	void start();
	void stop();
};

static timespec diff_ts(const timespec &t1, const timespec &t2);

#endif

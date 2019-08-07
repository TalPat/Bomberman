#ifndef _AMainLoop_hpp_
#define _AMainLoop_hpp_

#include <vector>
#include <ctime>

class AMainLoop
{
private:
	const double frameRate = 60.0;

	void loop();

	timespec _loopStart;
	timespec _loopEnd;

	bool _running = false;

protected:
	// This function will be called on every loop
	virtual void updateFunc() = 0;

	timespec _perFrameTime = {0, 1 * 1000000000 / static_cast<long>(frameRate)}; // Second to nano
	timespec _diff;
	timespec _sleep;

public:
	virtual ~AMainLoop() {}

	// Start the Main Loop
	void start();
	// Stops the Main Loop
	void stop();
};

static timespec diff_ts(const timespec &t1, const timespec &t2);

#endif

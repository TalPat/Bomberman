#ifndef _AMainLoop_hpp_
#define _AMainLoop_hpp_

#include <vector>
#include <ctime>

class AMainLoop
{
private:
	const double frameRate = 60.0;
	bool _running = false;

protected:
	// This function will be called on every loop
	virtual void updateFunc() = 0;

	const double perFrameSeconds = 1.0 / frameRate;

public:
	virtual ~AMainLoop() {}

	// Start the Main Loop
	void start();
	// Stops the Main Loop
	void stop();
};

#endif

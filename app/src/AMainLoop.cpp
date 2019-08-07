#include "AMainLoop.hpp"

#include <ctime>
#include <cmath>

void AMainLoop::start()
{
	this->_running = true;
	while (this->_running)
	{
		this->loop();
	}
}

void AMainLoop::stop()
{
	this->_running = false;
}

void AMainLoop::loop()
{
	clock_gettime(CLOCK_MONOTONIC, &this->_loopStart);

	updateFunc();

	clock_gettime(CLOCK_MONOTONIC, &this->_loopEnd);
	this->_diff = diff_ts(_loopEnd, _loopStart);
	this->_sleep = diff_ts(_diff, this->_perFrameTime);
	if (!_sleep.tv_sec && _sleep.tv_nsec < this->_perFrameTime.tv_nsec)
		nanosleep(&_sleep, NULL);
}

static timespec diff_ts(const timespec &t1, const timespec &t2)
{
	int sec = std::abs(t1.tv_sec - t2.tv_sec);
	int nano = std::abs(t1.tv_nsec - t2.tv_nsec);
	timespec ret;
	ret.tv_sec = sec + nano - (nano % 1000000000);
	ret.tv_nsec = nano % 1000000000;

	return ret;
}

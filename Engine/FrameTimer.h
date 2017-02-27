#pragma once
#include <chrono>

class FrameTimer
{
public:
	FrameTimer();
	float GetElapsedTime();
private:
	std::chrono::steady_clock::time_point last;
};
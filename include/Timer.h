#pragma once

class Timer
{
public:
	static float deltaTime;
	static float lastFrame;
	static unsigned int frameCount;

	static void Update();
	
	static float GetTime();

private:
	Timer() = delete;
	~Timer() = delete;

	Timer(const Timer& other) = delete;
	Timer& operator=(const Timer& other) = delete;
};


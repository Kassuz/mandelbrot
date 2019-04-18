#include "Timer.h"

#include <GLFW/glfw3.h>

float Timer::deltaTime = 0.1f;
float Timer::lastFrame = 0.0f;

unsigned int Timer::frameCount = 0;

void Timer::Update()
{
	float currentTimer = glfwGetTime();
	deltaTime = currentTimer - lastFrame;
	lastFrame = currentTimer;

	frameCount++;
}

float Timer::GetTime()
{
	return (float) glfwGetTime();
}

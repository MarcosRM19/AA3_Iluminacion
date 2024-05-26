#include "TimeManager.h"


TimeManager::TimeManager()
{
	elapsedTime = 0.f;
	lastFrameTime = glfwGetTime();
}

void TimeManager::Update()
{
	currentFrameTime = glfwGetTime();
	deltaTime = currentFrameTime - lastFrameTime;
	lastFrameTime = currentFrameTime;
	elapsedTime += deltaTime;
}

float TimeManager::GetElapsedTime()
{
	return elapsedTime;
}

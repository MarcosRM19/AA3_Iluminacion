#include "TimeManager.h"


TimeManager::TimeManager()
{
	lastFrameTime = glfwGetTime();
}

void TimeManager::Update()
{
	currentFrameTime = glfwGetTime();
	deltaTime = currentFrameTime - lastFrameTime;
	lastFrameTime = currentFrameTime;
}

float TimeManager::GetDeltaTime()
{
	return deltaTime;
}

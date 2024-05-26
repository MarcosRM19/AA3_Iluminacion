#pragma once
#include <GLFW/glfw3.h>

#define TIME_MANAGER TimeManager::Instance()

class TimeManager
{
private:

	TimeManager();

	TimeManager(const TimeManager&) = delete;
	TimeManager& operator =(const TimeManager&) = delete;

	float elapsedTime, lastFrameTime ,currentFrameTime, deltaTime; 

public:

	inline static TimeManager& Instance()
	{
		static TimeManager glManager;
		return glManager;
	}

	void Update();

	float GetElapsedTime();

};

#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ProgramManager.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define GL_MANAGER GLManager::Instance()

class GLManager
{
private:

	GLManager() = default;

	GLManager(const GLManager&) = delete;
	GLManager& operator =(const GLManager&) = delete;

public:

	inline static GLManager& Instance()
	{
		static GLManager glManager;
		return glManager;
	}

	GLFWwindow* window;

	void WindowsConfiguration();

	void ActivateFrontCulling();
	void ActivateBackCulling();
};

void ResizeWindow(GLFWwindow* _window, int _iFrameBufferWidth, int _iFrameBufferHeight);

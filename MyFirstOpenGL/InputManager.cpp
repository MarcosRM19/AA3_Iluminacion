#include "InputManager.h"


void InputManager::CheckKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	InputManager& manager = InputManager::Instance();
	if (action == GLFW_PRESS)
	{
		manager.keyState[key] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		manager.keyState[key] = false;
	}
}

void InputManager::CheckMousePosition(GLFWwindow* window, double xpos, double ypos)
{
	InputManager& manager = InputManager::Instance();
	manager.mouseX = xpos;
	manager.mouseY = ypos;
}

void InputManager::registerCallbacks(GLFWwindow* window)
{
	glfwSetKeyCallback(window, CheckKey);
	glfwSetCursorPosCallback(window, CheckMousePosition);
}

bool InputManager::isKeyPressed(int key)
{
	return keyState[key];
}

void InputManager::getMousePosition(double& x, double& y)
{
	x = mouseX;
	y = mouseY;
}
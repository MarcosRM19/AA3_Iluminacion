#pragma once
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <glm.hpp>

#define INPUT_MANAGER InputManager::Instance()

class InputManager
{
private:

	InputManager() = default;

	InputManager(const InputManager&) = delete;
	InputManager& operator =(const InputManager&) = delete;

	std::unordered_map<int, bool> keyState;
	glm::vec2 mouseInput;

	static void CheckKey(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void CheckMousePosition(GLFWwindow* window, double xpos, double ypos);

public:

	inline static InputManager& Instance()
	{
		static InputManager inputManager;
		return inputManager;
	}

	void registerCallbacks(GLFWwindow* window);

	bool IsKeyPressed(int key);
	glm::vec2 GetMousePosition();
};

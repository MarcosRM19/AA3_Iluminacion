#pragma once
#include "Object.h"
#include "ProgramManager.h"
#include "InputManager.h"

class Camera : public Object
{
private:
	float fov;
	float near;
	float far;

	glm::vec3 centerOfView;

	double lastX, lastY, xpos, ypos;
	bool firstMouse;

	float cameraSpeed;
	float sensitivity;

	float yaw, pitch;

	int isActive; 

public:

	Camera();

	virtual void Update(float _dt) override;

	void Inputs(GLFWwindow* _window, float _dt);

	void rotateCamera();
};

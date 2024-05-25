#pragma once
#include "Object.h"
#include "ProgramManager.h"

class Camera : public Object
{
private:
	float fov;
	float near;
	float far;

	glm::vec3 centerOfView;

	double lastX, lastY, xpos, ypos;
	bool firstMouse;

	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	float cameraSpeed;

	float yaw, pitch;

public:

	Camera();

	virtual void Update(float _dt) override;

	void Inputs(GLFWwindow* _window);

	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
};

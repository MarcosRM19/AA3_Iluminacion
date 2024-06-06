#include "Camera.h"

Camera::Camera()
	: Object(Transform(glm::vec3(0.f, 0.5f, 4.f), glm::vec3(0.f))),
	fov(45.f), near(0.1f), far(10.f)
{
	cameraSpeed = 1;
	sensitivity = 0.1f;
	yaw = -90.f;
	pitch = 0.0f;
	firstMouse = true;

	//SpotLight variables
	isActive = 0;
	innerConeAngle = glm::radians(25.0f);
	outerConeAngle = glm::radians(35.0f);
	maxDistance = 2.0f;
};

void Camera::Update(float _dt)
{
	// Matrix generation
	glm::mat4 view = glm::lookAt(transform.position, transform.position + transform.forward, transform.up);
	glm::mat4 projection = glm::perspective(glm::radians(fov), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, near, far);

	//Pass view and projection information to all programs
	for (GLuint program : PROGRAM_MANAGER.compiledPrograms)
	{
		glUseProgram(program);
		glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	}

	//Pass SpotLigh variables to the program that used by the models
	glUseProgram(PROGRAM_MANAGER.compiledPrograms[0]);
	glUniform3fv(glGetUniformLocation(PROGRAM_MANAGER.compiledPrograms[0], "spotLight"), 1, glm::value_ptr(transform.position));
	glUniform1f(glGetUniformLocation(PROGRAM_MANAGER.compiledPrograms[0], "isActive"), isActive);
	glUniform1f(glGetUniformLocation(PROGRAM_MANAGER.compiledPrograms[0], "maxDistance"), maxDistance);
	glUniform1f(glGetUniformLocation(PROGRAM_MANAGER.compiledPrograms[0], "innerConeAngle"), innerConeAngle);
	glUniform1f(glGetUniformLocation(PROGRAM_MANAGER.compiledPrograms[0], "outerConeAngle"), outerConeAngle);
}

void Camera::Inputs(GLFWwindow* _window, float _dt)
{
	//camera inputs
	if (INPUT_MANAGER.IsKeyPressed(GLFW_KEY_W))
	{
		transform.position += transform.forward * cameraSpeed * _dt;
	}
	if (INPUT_MANAGER.IsKeyPressed(GLFW_KEY_S))
	{
		transform.position -= transform.forward * cameraSpeed * _dt;
	}
	if (INPUT_MANAGER.IsKeyPressed(GLFW_KEY_A))
	{
		transform.position -= glm::normalize(glm::cross(transform.forward, transform.up)) * cameraSpeed * _dt;
	}
	if (INPUT_MANAGER.IsKeyPressed(GLFW_KEY_D))
	{
		transform.position += glm::normalize(glm::cross(transform.forward, transform.up)) * cameraSpeed * _dt;
	}
	if (INPUT_MANAGER.IsKeyPressed(GLFW_KEY_F))
	{
		if (isActive == 1)
			isActive = 0;
		else
			isActive = 1;
	}

	//Function that rotate de camera with the information of xPos and yPos
	rotateCamera();
}

void Camera::rotateCamera()
{
	//Set x and y position in the area of the windows
	xpos = INPUT_MANAGER.GetMousePosition().x;
	ypos = INPUT_MANAGER.GetMousePosition().y;

	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	//layer movement on the Y axis
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	//Set new forward values
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	transform.forward = glm::normalize(front);
}


#include "Camera.h"

Camera::Camera()
	: Object(Transform(glm::vec3(0.f, 0.5f, 4.f), glm::vec3(0.f))),
	fov(45.f), near(0.1f), far(10.f)
{
	cameraSpeed = 1;
	yaw = -90.f;
	pitch = 0.0f;
	firstMouse = true;

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

	//Indicar a la tarjeta GPU que programa debe usar
	for (GLuint program : PROGRAM_MANAGER.compiledPrograms)
	{
		glUseProgram(program);
		glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	}

	glUseProgram(PROGRAM_MANAGER.compiledPrograms[0]);
	glUniform3fv(glGetUniformLocation(PROGRAM_MANAGER.compiledPrograms[0], "spotLight"), 1, glm::value_ptr(transform.position));
	glUniform1f(glGetUniformLocation(PROGRAM_MANAGER.compiledPrograms[0], "isActive"), isActive);
	glUniform1f(glGetUniformLocation(PROGRAM_MANAGER.compiledPrograms[0], "maxDistance"), maxDistance);
	glUniform1f(glGetUniformLocation(PROGRAM_MANAGER.compiledPrograms[0], "innerConeAngle"), innerConeAngle);
	glUniform1f(glGetUniformLocation(PROGRAM_MANAGER.compiledPrograms[0], "outerConeAngle"), outerConeAngle);
}

void Camera::Inputs(GLFWwindow* _window, float _dt)
{
	if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS) 
	{
		transform.position += transform.forward * cameraSpeed * _dt;
	}
	if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS) 
	{
		transform.position -= transform.forward * cameraSpeed * _dt;
	}
	if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS) 
	{
		transform.position -= glm::normalize(glm::cross(transform.forward, transform.up)) * cameraSpeed * _dt;
	}
	if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS) 
	{
		transform.position += glm::normalize(glm::cross(transform.forward, transform.up)) * cameraSpeed * _dt;
	}
	if (glfwGetKey(_window, GLFW_KEY_F) == GLFW_PRESS)
	{
		if (isActive == 1)
			isActive = 0;
		else
			isActive = 1;
	}
	glfwGetCursorPos(_window, &xpos, &ypos);
	mouse_callback(_window, xpos, ypos);
}

void Camera::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // Invertido porque los sistemas de coordenadas de Y van al revés
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// Asegurarse de que pitch no pase de los límites
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	transform.forward = glm::normalize(front);
}


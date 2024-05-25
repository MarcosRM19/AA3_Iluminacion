#include "Camera.h"

Camera::Camera()
	: Object(Transform(glm::vec3(0.f), glm::vec3(0.f))),
	fov(0.f), near(0.1f), far(10.f), angleIncrease(glm::vec3(0.f, 1.f, 0.f)), typeOfView(TypeOfView::ORBIT)
{
	ResetTypeOfView(typeOfView);
	transform.position =
	{
		eyeOrientation.x + distanceToCenter * sin(transform.rotation.y * (M_PI / 180)) * cos(transform.rotation.z * (M_PI / 180)),
		eyeOrientation.y + distanceToCenter * sin(transform.rotation.z * (M_PI / 180)),
		eyeOrientation.z + distanceToCenter * cos(transform.rotation.y * (M_PI / 180)) * cos(transform.rotation.z * (M_PI / 180))
	};
};

Camera::Camera(Transform _transform, float _fov, float _near, float _far,
	glm::vec3 _centerOfView, float _distanceToCenter, glm::vec3 _eyeOrientation, glm::vec3 _angleIncrease)
	: Object(_transform), fov(_fov), near(_near), far(_far),
	distanceToCenter(_distanceToCenter), angleIncrease(_angleIncrease),
	eyeOrientation(_eyeOrientation), centerOfView(_centerOfView), typeOfView(TypeOfView::ORBIT)
{};


void Camera::Update(float _dt)
{
	// Matrix generation
	glm::mat4 view = glm::lookAt(transform.position, centerOfView, transform.up);
	glm::mat4 projection = glm::perspective(glm::radians(fov), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, near, far);

	//Indicar a la tarjeta GPU que programa debe usar
	for (GLuint program : PROGRAM_MANAGER.compiledPrograms)
	{
		glUseProgram(program);
		glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	}
}

void Camera::Inputs(GLFWwindow* _window)
{
	if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS) {

		transform.position.z -= 0.01;
	}
	if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS) {

		transform.position.z += 0.01;
	}
	if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS) {


	}
	if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS) {


	}
	lastXpos = xpos;
	lastYpos = ypos;
	glfwGetCursorPos(_window, &xpos, &ypos);
	if (xpos > lastXpos)
	{
		std::cout << "Derecha" << std::endl;
	}
	if (xpos < lastXpos)
	{
		std::cout << "Izquierda" << std::endl;
	}
	if (ypos < lastYpos)
	{
		std::cout << "Arriba" << std::endl;
	}
	if (ypos > lastYpos)
	{
		std::cout << "Abajo" << std::endl;
	}
}

void Camera::ResetTypeOfView(TypeOfView _typeOfView)
{
	typeOfView = _typeOfView;
	switch (typeOfView)
	{
	case Camera::TypeOfView::ORBIT:

		transform.rotation = glm::vec3(0.f);
		centerOfView = glm::vec3(0.f, 0.25f, 1.2f);
		eyeOrientation = centerOfView + glm::vec3(0.f, 0.5f, 0.f);
		distanceToCenter = 1.25f;
		fov = 45.0f;

		break;
	case Camera::TypeOfView::PLANE_TROLL_1:

		transform.rotation = glm::vec3(0.f, 80.f, 0.f);
		centerOfView = glm::vec3(-0.2f, 0.25f, 1.3f) + glm::vec3(0.f, 0.1f, 0.f);
		eyeOrientation = centerOfView;
		distanceToCenter = 0.4f;
		fov = 45.f;

		break;
	case Camera::TypeOfView::PLANE_TROLL_3:

		transform.rotation = glm::vec3(0.f, 280.f, 0.f);
		centerOfView = glm::vec3(0.2f, 0.25f, 1.3f) + glm::vec3(0.f, 0.19f, 0.f);
		eyeOrientation = centerOfView;
		distanceToCenter = 0.4f;
		fov = 10.f;

		break;
	case Camera::TypeOfView::DOLLY_ZOOM:

		transform.rotation = glm::vec3(0.f, 1.f, 0.f);
		centerOfView = glm::vec3(0.f, 0.25f, 1.1f) + glm::vec3(0.f, 0.25f, 0.f);
		eyeOrientation = centerOfView + glm::vec3(0.f, 0.f, 0.f);
		distanceToCenter = 0.85f;

		break;
	default:
		break;
	}
}
void Camera::CalculTypeOfView()
{
	switch (typeOfView)
	{
	case Camera::TypeOfView::ORBIT:
		transform.rotation += angleIncrease * scaleTime;
		break;

	case Camera::TypeOfView::DOLLY_ZOOM:
		distanceToCenter -= 0.001f;
		fov = 2.0f * atan(0.75 * 0.5f / distanceToCenter) * 360 / (M_PI * 2);

		if (distanceToCenter < 0.4f)
			ResetTypeOfView(TypeOfView::ORBIT);
		break;

	default:
		break;
	}
};

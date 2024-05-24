#pragma once
#include "Object.h"
#include "ProgramManager.h"

class Camera : public Object
{
private:

	enum class TypeOfView
	{
		ORBIT = 0,
		PLANE_TROLL_1 = 1,
		PLANE_TROLL_3 = 2,
		DOLLY_ZOOM = 3
	};
	TypeOfView typeOfView;

	float fov;
	float near;
	float far;

	glm::vec3 centerOfView;
	float distanceToCenter;
	glm::vec3 eyeOrientation;
	glm::vec3 angleIncrease;

	void ResetTypeOfView(TypeOfView _typeOfView);
	void CalculTypeOfView();

public:

	Camera();

	Camera(Transform _transform, float _fov, float _near, float _far,
		glm::vec3 _centerOfView, float _distanceToCenter, glm::vec3 _eyeOrientation, glm::vec3 _angleIncrease);

	virtual void Update(float _dt) override;

	void Inputs(GLFWwindow* _window);
};

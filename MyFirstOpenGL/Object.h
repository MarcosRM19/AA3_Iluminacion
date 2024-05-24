#pragma once
#include <glm.hpp>
#include <vector>
#include <GL/glew.h>
#include <gtc/type_ptr.hpp>
#include <stb_image.h>

#include "GLManager.h"
#include "Transform.h"
#include "MatrixUtilities.h"

class Object
{
protected:

	Transform transform;
	float scaleTime; // 0 < scaleTime < n 

public:

	Object(Transform _transform, float _scaleTime = 1.f)
		:transform(_transform), scaleTime(_scaleTime)
	{};

	virtual void Update(float _dt) = 0;

	inline void StopMovement();
};



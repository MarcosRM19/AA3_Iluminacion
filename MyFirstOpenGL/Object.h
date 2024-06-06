#pragma once
#include <glm.hpp>
#include <vector>
#include <GL/glew.h>
#include <gtc/type_ptr.hpp>
#include <stb_image.h>

#include "GLManager.h"
#include "Transform.h"
#include "MatrixUtilities.h"

#include "Texture.h"
#include "Model.h"

class Object
{
protected:
	Transform transform;

public:
	Object(Transform _transform);

	virtual void Update(float _dt) = 0;

	virtual void ApplyMatrix() = 0;
};



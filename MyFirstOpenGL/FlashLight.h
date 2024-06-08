#pragma once
#include "Transform.h"
#include "ProgramManager.h"
#include <gtc/type_ptr.hpp>

class FlashLight
{
private:
	float outerConeAngle, innerConeAngle, intensity;

public:
	FlashLight();

	void Update(Transform transform, bool isAcitve);
};

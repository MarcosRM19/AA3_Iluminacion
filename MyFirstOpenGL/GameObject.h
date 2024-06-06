#pragma once
#include "Object.h"

class GameObject : public Object
{
private:
	Model model;

public:
	GameObject(glm::vec3 position, float maxScale, float minScale, Model model);

	virtual void Update(float _dt) override;
};


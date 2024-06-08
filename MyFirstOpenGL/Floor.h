#pragma once
#include "Object.h"

class Floor : public Object
{
private:
	Model model;

public:
	Floor(glm::vec3 position, Model model);

	virtual void Update(float _dt) override;
};


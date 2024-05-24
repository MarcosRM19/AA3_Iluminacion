#pragma once
#include "Object.h"

class SpawnPoint : public Object
{
private:
	bool modelLocated;

public:
	SpawnPoint(Transform transform);

	virtual void Update(float _dt) {}

	bool GetModelLocated();

	glm::vec3 GetPosition();
};
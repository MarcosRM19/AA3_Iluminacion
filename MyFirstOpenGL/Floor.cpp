#include "Floor.h"

Floor::Floor(glm::vec3 position, Model model) 
	: Object(Transform(position, glm::vec3(0.f, 1.0f, 0.f), glm::vec3(1.0f))), model(model)
{}

void Floor::Update(float _dt)
{
	model.Render(transform, glm::vec4(1.0,1.0,1.0,1.0));
}


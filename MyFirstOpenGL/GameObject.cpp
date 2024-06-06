#include "GameObject.h"

GameObject::GameObject(glm::vec3 position, float maxScale, float minScale, Model model)
	: Object(Transform(position, glm::vec3(0.f, rand() % 360, 0.f), glm::vec3(0.2))),
		 model(model)
{
}

void GameObject::Update(float _dt)
{
	model.Render(transform);
}


#include "GameObject.h"

GameObject::GameObject(glm::vec3 position, float maxScale, float minScale, Model model)
	: Object(Transform(position, glm::vec3(0.f, rand() % 360, 0.f), glm::vec3(minScale + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxScale - minScale)))))),
		 model(model)
{
}

void GameObject::Update(float _dt)
{
	model.Render(transform, glm::vec4(1.0, 1.0, 1.0, 1.0));
}


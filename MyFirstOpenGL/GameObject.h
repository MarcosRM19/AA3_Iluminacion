#pragma once
#include "Object.h"
#include "Texture.h"
#include "Model.h"

class GameObject : public Object
{
private:
	glm::vec4 color;
	GLuint renderMode;
	Model model;

public:

	GameObject(glm::vec3 position, glm::vec4 _color, float maxScale, float minScale, Model model);


	virtual void Update(float _dt) override;
};


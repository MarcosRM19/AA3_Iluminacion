#pragma once
#include "Object.h"
#include "Texture.h"
#include "Model.h"

class GameObject : public Object
{
private:

	GLuint program;

	glm::vec4 color;

	GLuint renderMode;
	Texture* texture;

	GLint modelVAO, modelNumVertex;

public:

	GameObject(GLuint _program,
		glm::vec3 position, glm::vec4 _color,
		GLint modelVAO, GLint modelNumVertex, Texture* texture, GLuint _renderMode);


	virtual void Update(float _dt) override;
	virtual void Render();
};


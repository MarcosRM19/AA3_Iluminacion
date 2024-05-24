#include "GameObject.h"

GameObject::GameObject(GLuint _program, glm::vec3 position, glm::vec4 _color,
	GLint modelVAO, GLint modelNumVertex, Texture* _texture, GLuint _renderMode, float maxScale, float minScale)
	: Object(Transform(position, glm::vec3(0.f, rand() % 360 + 1, 0.f), glm::vec3(minScale + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxScale - minScale)))))),
		program(_program), color(_color), modelVAO(modelVAO), modelNumVertex(modelNumVertex), texture(_texture), renderMode(_renderMode)
{};


void GameObject::Update(float _dt)
{
	//Indicar a la tarjeta GPU que programa debe usar
	glUseProgram(program);

	//Definir la matriz de traslacion, rotacion y escalado
	glm::mat4 translationMatrix = MatrixUtilities::GenerateTranslationMatrix(transform.position);
	glm::mat4 rotationMatrix = MatrixUtilities::GenerateRotationMatrix(transform.rotation, transform.rotation.x);
	rotationMatrix *= MatrixUtilities::GenerateRotationMatrix(transform.rotation, transform.rotation.y);
	rotationMatrix *= MatrixUtilities::GenerateRotationMatrix(transform.rotation, transform.rotation.z);
	glm::mat4 scaleMatrix = MatrixUtilities::GenerateScaleMatrix(transform.scale);

	//Asignar valores iniciales al programa
	glUniform2f(glGetUniformLocation(program, "windowSize"), WINDOW_WIDTH, WINDOW_HEIGHT);

	if (texture != nullptr)
	{
		//Asignar valor variable de textura a usar.
		glUniform1i(glGetUniformLocation(program, "textureSampler"), texture->textureIndex);
	}

	// Pasar las matrices
	glUniformMatrix4fv(glGetUniformLocation(program, "translationMatrix"), 1, GL_FALSE, glm::value_ptr(translationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(program, "rotationMatrix"), 1, GL_FALSE, glm::value_ptr(rotationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(program, "scaleMatrix"), 1, GL_FALSE, glm::value_ptr(scaleMatrix));

	// Pasar el color en que queremos pintar el game object
	glUniform4fv(glGetUniformLocation(program, "ambientColor"), 1, glm::value_ptr(color));
}

void GameObject::Render()
{
	//Vinculo su VAO para ser usado
	glBindVertexArray(modelVAO);

	// Dibujamos
	glDrawArrays(renderMode, 0, modelNumVertex);

	//Desvinculamos VAO
	glBindVertexArray(0);
}


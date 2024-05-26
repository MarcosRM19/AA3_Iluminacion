#include "GameObject.h"

GameObject::GameObject(glm::vec3 position, glm::vec4 _color, float maxScale, float minScale, Model model)
	: Object(Transform(position, glm::vec3(0.f, rand() % 360 + 1, 0.f), glm::vec3(minScale + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxScale - minScale)))))),
		color(_color), model(model)
{};


void GameObject::Update(float _dt)
{
	model.Render();

	//Definir la matriz de traslacion, rotacion y escalado
	glm::mat4 translationMatrix = MatrixUtilities::GenerateTranslationMatrix(transform.position);
	glm::mat4 rotationMatrix = MatrixUtilities::GenerateRotationMatrix(transform.rotation, transform.rotation.x);
	rotationMatrix *= MatrixUtilities::GenerateRotationMatrix(transform.rotation, transform.rotation.y);
	rotationMatrix *= MatrixUtilities::GenerateRotationMatrix(transform.rotation, transform.rotation.z);
	glm::mat4 scaleMatrix = MatrixUtilities::GenerateScaleMatrix(transform.scale);

	//Asignar valores iniciales al programa
	glUniform2f(glGetUniformLocation(model.GetProgram(), "windowSize"), WINDOW_WIDTH, WINDOW_HEIGHT);

	// Pasar las matrices
	glUniformMatrix4fv(glGetUniformLocation(model.GetProgram(), "translationMatrix"), 1, GL_FALSE, glm::value_ptr(translationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(model.GetProgram(), "rotationMatrix"), 1, GL_FALSE, glm::value_ptr(rotationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(model.GetProgram(), "scaleMatrix"), 1, GL_FALSE, glm::value_ptr(scaleMatrix));

	// Pasar el color en que queremos pintar el game object
	glUniform4fv(glGetUniformLocation(model.GetProgram(), "ambientColor"), 1, glm::value_ptr(color));
}


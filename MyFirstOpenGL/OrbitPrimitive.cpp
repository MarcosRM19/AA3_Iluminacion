#include "OrbitPrimitive.h"

OrbitPrimitive::OrbitPrimitive(GLuint _program, glm::vec3 position, glm::vec4 _color,  GLint modelVAO, GLint modelNumVertex, GLuint _renderMode, float initAngle)
    : Object(Transform(position, glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.3))), modelVAO(modelVAO), modelNumVertex(modelNumVertex), renderMode(_renderMode),
	program(_program), color(_color), initAngle(initAngle)
{}

void OrbitPrimitive::Update(float _dt)
{
	//Indicar a la tarjeta GPU que programa debe usar
	glUseProgram(program);

	CalculateOrbit(_dt);

	//Definir la matriz de traslacion, rotacion y escalado
	glm::mat4 translationMatrix = MatrixUtilities::GenerateTranslationMatrix(transform.position);
	glm::mat4 rotationMatrix = MatrixUtilities::GenerateRotationMatrix(transform.rotation, transform.rotation.x);
	rotationMatrix *= MatrixUtilities::GenerateRotationMatrix(transform.rotation, transform.rotation.y);
	rotationMatrix *= MatrixUtilities::GenerateRotationMatrix(transform.rotation, transform.rotation.z);
	glm::mat4 scaleMatrix = MatrixUtilities::GenerateScaleMatrix(transform.scale);

	//Asignar valores iniciales al programa
	glUniform2f(glGetUniformLocation(program, "windowSize"), WINDOW_WIDTH, WINDOW_HEIGHT);

	// Pasar las matrices
	glUniformMatrix4fv(glGetUniformLocation(program, "translationMatrix"), 1, GL_FALSE, glm::value_ptr(translationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(program, "rotationMatrix"), 1, GL_FALSE, glm::value_ptr(rotationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(program, "scaleMatrix"), 1, GL_FALSE, glm::value_ptr(scaleMatrix));

	// Pasar el color en que queremos pintar el game object
	glUniform4fv(glGetUniformLocation(program, "ambientColor"), 1, glm::value_ptr(color));
}

void OrbitPrimitive::Render()
{
    //Vinculo su VAO para ser usado
    glBindVertexArray(modelVAO);

    // Dibujamos
    glDrawArrays(renderMode, 0, modelNumVertex);

    //Desvinculamos VAO
    glBindVertexArray(0);
}

void OrbitPrimitive::CalculateOrbit(float _dt)
{
	float angle = initAngle + 2.0f * M_PI * (_dt / 20.f);
	transform.position.x = 1.f * cos(angle);
	transform.position.y = 1.f * sin(angle);
}

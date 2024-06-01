#include "OrbitPrimitive.h"

OrbitPrimitive::OrbitPrimitive(glm::vec4 _color, Model model, float initAngle, float radius, float orbitTime, bool interpolateColor)
    : Object(Transform(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.3))), color(_color), model(model), initAngle(initAngle), radius(radius), orbitTime(orbitTime), 
	interpolateColor(interpolateColor)
{
	elapsedTime = 0.0f;
	angle = initAngle;
}

void OrbitPrimitive::Update(float _dt)
{
	//Indicar a la tarjeta GPU que programa debe usar
	model.Render();

	CalculateOrbit(_dt);

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

	ApplyLight();
}

void OrbitPrimitive::ApplyLight()
{
	glUseProgram(PROGRAM_MANAGER.compiledPrograms[0]);

	if (transform.position.y > 0)
	{
		glUniform3fv(glGetUniformLocation(PROGRAM_MANAGER.compiledPrograms[0], "sourceLight"), 1, glm::value_ptr(transform.position));
	}

	if (interpolateColor)
	{
		CalculateInterpolation();
		glUniform1f(glGetUniformLocation(PROGRAM_MANAGER.compiledPrograms[0], "t"), alphaValue);
		std::cout << alphaValue << std::endl;
	}
}

void OrbitPrimitive::CalculateOrbit(float _dt)
{
	elapsedTime += _dt;
	angle = initAngle + 2.0f * M_PI * (elapsedTime / orbitTime);
	transform.position.x = radius * cos(angle);
	transform.position.y = radius * sin(angle);
}

void OrbitPrimitive::CalculateInterpolation()
{
	// Normaliza el ángulo para que esté en el rango [0, 2 * M_PI]
	angle = fmod(angle, 2.0f * M_PI);
	if (angle < 0.0f) {
		angle += 2.0f * M_PI;
	}

	if (transform.position.x < 0)
	{
		if (angle <= M_PI / 2.0f) 
		{
			alphaValue = 0.5f + (angle / (M_PI / 2.0f)) * 0.5f;
		}
		else 
		{
			alphaValue = 1.0f - ((angle - M_PI / 2.0f) / (M_PI / 2.0f)) * 0.5f;
		}
		glUniform3fv(glGetUniformLocation(PROGRAM_MANAGER.compiledPrograms[0], "colorA"), 1, glm::value_ptr(colors[2]));
		glUniform3fv(glGetUniformLocation(PROGRAM_MANAGER.compiledPrograms[0], "colorB"), 1, glm::value_ptr(colors[1]));
	}
	else
	{
		if (angle <= M_PI / 2.0f)
		{
			alphaValue = 0.5f + (angle / (M_PI / 2.0f)) * 0.5f;
		}
		else 
		{
			alphaValue = (1.0f - ((angle - M_PI / 2.0f) / (M_PI / 2.0f)) * 0.5f) * -1;
		}
		glUniform3fv(glGetUniformLocation(PROGRAM_MANAGER.compiledPrograms[0], "colorA"), 1, glm::value_ptr(colors[0]));
		glUniform3fv(glGetUniformLocation(PROGRAM_MANAGER.compiledPrograms[0], "colorB"), 1, glm::value_ptr(colors[1]));
	}
}

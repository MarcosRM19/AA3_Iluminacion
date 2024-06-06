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
	model.Render();
	CalculateOrbit(_dt);
	ApplyMatrix();
	ApplyLight();
}

void OrbitPrimitive::ApplyMatrix()
{
	//Define the translation, rotation and scaling matrix
	glm::mat4 translationMatrix = MatrixUtilities::GenerateTranslationMatrix(transform.position);
	glm::mat4 rotationMatrix = MatrixUtilities::GenerateRotationMatrix(transform.rotation, transform.rotation.x);
	rotationMatrix *= MatrixUtilities::GenerateRotationMatrix(transform.rotation, transform.rotation.y);
	rotationMatrix *= MatrixUtilities::GenerateRotationMatrix(transform.rotation, transform.rotation.z);
	glm::mat4 scaleMatrix = MatrixUtilities::GenerateScaleMatrix(transform.scale);

	//Assign initial values to the program
	glUniform2f(glGetUniformLocation(model.GetProgram(), "windowSize"), WINDOW_WIDTH, WINDOW_HEIGHT);

	//Pass the matrixs
	glUniformMatrix4fv(glGetUniformLocation(model.GetProgram(), "translationMatrix"), 1, GL_FALSE, glm::value_ptr(translationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(model.GetProgram(), "rotationMatrix"), 1, GL_FALSE, glm::value_ptr(rotationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(model.GetProgram(), "scaleMatrix"), 1, GL_FALSE, glm::value_ptr(scaleMatrix));

	//Pass the color in which we want to paint the game object
	glUniform4fv(glGetUniformLocation(model.GetProgram(), "ambientColor"), 1, glm::value_ptr(color));
}

void OrbitPrimitive::ApplyLight()
{
	//Active the program used by the gameobjects affected by the lights
	glUseProgram(PROGRAM_MANAGER.compiledPrograms[0]);

	//Find out if the position of the orbit objects is upper the 0, that mean that is being seen and has to apply light to the gameobjects
	if (transform.position.y > 0)
	{
		glUniform3fv(glGetUniformLocation(PROGRAM_MANAGER.compiledPrograms[0], "sourceLight"), 1, glm::value_ptr(transform.position));
	}

	//Only 1 of the orbit objects going to calculate the interpolation to try to simplify the method
	if (interpolateColor)
	{
		CalculateInterpolation();
		glUniform1f(glGetUniformLocation(PROGRAM_MANAGER.compiledPrograms[0], "t"), alphaValue);
	}
}

void OrbitPrimitive::CalculateOrbit(float _dt)
{
	//Move the x and y of the orbit object recalculating the angle in the world with the time that has passed
	elapsedTime += _dt;
	angle = initAngle + 2.0f * M_PI * (elapsedTime / orbitTime);
	transform.position.x = radius * cos(angle);
	transform.position.y = radius * sin(angle);
}

void OrbitPrimitive::CalculateInterpolation()
{
	//Normalizes the angle to be in the range [0, 2 * M_PI]
	angle = fmod(angle, 2.0f * M_PI);
	if (angle < 0.0f) {
		angle += 2.0f * M_PI;
	}

	//How we work with 2 different types of blue and 1 yellow we have 2 interpolation, when the sun is rising and when it is going down, so we calculate a value between 0 and 1 according to the angle
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

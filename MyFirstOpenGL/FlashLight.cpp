#include "FlashLight.h"

FlashLight::FlashLight()
{
	outerConeAngle = 20.0f;
	innerConeAngle = 10.0f;
	intensity = 0.7;
}

void FlashLight::Update(Transform transform, bool isAcitve)
{
	//Pass SpotLigh variables to the program that used by the models
	glUseProgram(PROGRAM_MANAGER.compiledPrograms[0]);
	glUniform3fv(glGetUniformLocation(PROGRAM_MANAGER.compiledPrograms[0], "spotLight"), 1, glm::value_ptr(transform.position));
	glUniform3fv(glGetUniformLocation(PROGRAM_MANAGER.compiledPrograms[0], "spotLightDirection"), 1, glm::value_ptr(transform.forward));
	glUniform1f(glGetUniformLocation(PROGRAM_MANAGER.compiledPrograms[0], "isActive"), (int)isAcitve);
	glUniform1f(glGetUniformLocation(PROGRAM_MANAGER.compiledPrograms[0], "outerConeAngle"), outerConeAngle);
	glUniform1f(glGetUniformLocation(PROGRAM_MANAGER.compiledPrograms[0], "innerConeAngle"), innerConeAngle);
	glUniform1f(glGetUniformLocation(PROGRAM_MANAGER.compiledPrograms[0], "intensity"), intensity);
}

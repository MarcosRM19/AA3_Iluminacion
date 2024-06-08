#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#define M_PI 3.1415926535897932384626433832795

static class MatrixUtilities
{
public:

	static glm::mat4 GenerateTranslationMatrix(glm::vec3 _translation);

	static glm::mat4 GenerateRotationMatrix(glm::vec3 _axis, float _fDegrees);

	static glm::mat4 GenerateScaleMatrix(glm::vec3 _scaleAxis);
};
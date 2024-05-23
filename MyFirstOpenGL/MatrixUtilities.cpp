#include "MatrixUtilities.h"

glm::mat4 MatrixUtilities::GenerateTranslationMatrix(glm::vec3 _translation)
{
    return glm::translate(glm::mat4(1.f), _translation);
}

glm::mat4 MatrixUtilities::GenerateRotationMatrix(glm::vec3 _axis, float _fDegrees)
{
    return glm::rotate(glm::mat4(1.f), glm::radians(_fDegrees), glm::normalize(_axis));
}

glm::mat4 MatrixUtilities::GenerateScaleMatrix(glm::vec3 _scaleAxis)
{
    return glm::scale(glm::mat4(1.f), _scaleAxis);
}

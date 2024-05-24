#include "SpwanPoint.h"

SpawnPoint::SpawnPoint(Transform transform)
    :Object(transform)
{
    modelLocated = false;
}

void SpawnPoint::SetModelLocated(bool isLocated)
{
    modelLocated = isLocated;
}

bool SpawnPoint::GetModelLocated()
{
    return modelLocated;
}

glm::vec3 SpawnPoint::GetPosition()
{
    return transform.position;
}

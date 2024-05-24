#include "SpwanPoint.h"

SpawnPoint::SpawnPoint(Transform transform)
    :Object(transform){}

bool SpawnPoint::GetModelLocated()
{
    return modelLocated;
}

glm::vec3 SpawnPoint::GetPosition()
{
    return transform.position;
}

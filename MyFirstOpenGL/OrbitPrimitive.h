#pragma once
#include "Object.h"

class OrbitPrimitive : public Object
{
private:
    glm::vec4 color;
    Model model;

    float initAngle, elapsedTime, radius, orbitTime;

public:
    OrbitPrimitive(glm::vec4 _color, Model model, float initAngle, float radius, float orbitTime);
    
    virtual void Update(float _dt) override;

    void CalculateOrbit(float _dt);
};

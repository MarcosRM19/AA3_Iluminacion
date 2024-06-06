#pragma once
#include "Object.h"

class OrbitPrimitive : public Object
{
private:
    glm::vec4 color;
    Model model;

    float initAngle, elapsedTime, radius, orbitTime, angle, alphaValue, coeficientValue;
    bool interpolateColor;

    std::vector<glm::vec3> colors{ glm::vec3(0.0, 0.129, 0.306) , glm::vec3(1.0, 0.819, 0.384) , glm::vec3(0.0, 0.066, 0.266) };

public:
    OrbitPrimitive(glm::vec4 _color, Model model, float initAngle, float radius, float orbitTime, float coeficientValue, bool interpolateColor);
    
    virtual void Update(float _dt) override;

    void ApplyLight();

    void CalculateOrbit(float _dt);

    void CalculateInterpolation();
};

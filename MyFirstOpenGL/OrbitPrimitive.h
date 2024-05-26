#pragma once
#include "Object.h"

class OrbitPrimitive : public Object
{
private:

    GLint modelVAO, modelNumVertex;
    GLuint renderMode;

    GLuint program;
    glm::vec4 color;

    float initAngle;

public:
    OrbitPrimitive(GLuint _program, glm::vec3 position, glm::vec4 _color, GLint modelVAO, GLint modelNumVertex, GLuint _renderMode, float initAngle);
    
    virtual void Update(float _dt) override;
    virtual void Render();

    void CalculateOrbit(float _dt);
};

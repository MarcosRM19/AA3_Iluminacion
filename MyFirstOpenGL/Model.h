#ifndef MODEL_H
#define MODEL_H

#include <glm.hpp>
#include <GL/glew.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <gtc/type_ptr.hpp>>

#include "Texture.h"
#include "ProgramManager.h"
#include "Transform.h"
#include "GLManager.h"
#include "MatrixUtilities.h"


class Model
{
private:

    GLuint VAO, VBO, uvVBO, normalsVBO;
    GLuint colorVBO;
    unsigned int numVertexs;

    GLuint program, renderMode;
    Texture* texture;

public:

    // Constructor for game objects with texture
    Model(const std::vector<float>& _vertexs, const std::vector<float>& _uvs, const std::vector<float>& _normals, GLuint _program, Texture* texture, GLuint renderMode);
    // Constructor for primitives
    Model(const std::vector<float>& _vertexs, GLuint _program, Texture* texture, GLuint renderMode);

    void Render(Transform transform);
    void ApplyMatrix(Transform transform);

    // GETTERS 
    GLuint GetProgram();
};

#endif

#include "Model.h"

Model::Model(const std::vector<float>& _vertexs, const std::vector<float>& _uvs, const std::vector<float>& _normals, GLuint _program, Texture* texture, GLuint renderMode)
    :program(_program), texture(texture), renderMode(renderMode)
{

    //Almaceno la cantidad de vertices que habra
    this->numVertexs = _vertexs.size() / 3;

    //Generamos VAO/VBO
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->uvVBO);
    glGenBuffers(1, &this->normalsVBO);

    //Defino el VAO creado como activo
    glBindVertexArray(this->VAO);

    //Defino el VBO de las posiciones como activo, le paso los datos y lo configuro
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, _vertexs.size() * sizeof(float), _vertexs.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // Definimos el VBO de las coordenadas de textura como activo, le pasamos los datos y lo configuramos
    glBindBuffer(GL_ARRAY_BUFFER, this->uvVBO);
    glBufferData(GL_ARRAY_BUFFER, _uvs.size() * sizeof(float), _uvs.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

    // Definimos el VBO de las coordenadas de textura como activo, le pasamos los datos y lo configuramos
    glBindBuffer(GL_ARRAY_BUFFER, this->normalsVBO);
    glBufferData(GL_ARRAY_BUFFER, _normals.size() * sizeof(float), _normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    //Activamos ambos atributos para ser usados
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    //Desvinculamos VAO y VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

Model::Model(const std::vector<float>& _vertexs, GLuint _program, Texture* texture, GLuint renderMode)
    :program(_program), texture(texture), renderMode(renderMode)
{
    //Almaceno la cantidad de vertices que habra
    this->numVertexs = _vertexs.size() / 3;

    //Generamos VAO/VBO
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);

    //Defino el VAO creado como activo
    glBindVertexArray(this->VAO);

    //Defino el VBO de las posiciones como activo, le paso los datos y lo configuro
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, _vertexs.size() * sizeof(float), _vertexs.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    //Activamos ambos atributos para ser usados
    glEnableVertexAttribArray(0);

    //Desvinculamos VAO y VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Model::Render(Transform transform)
{
    //Link your VAO to be used
    glBindVertexArray(VAO);

    glUseProgram(program);

    if (texture != nullptr)
    {
        glUniform1i(glGetUniformLocation(program, "textureSampler"), texture->textureIndex);
    }

    ApplyMatrix(transform);

    //Draw
    glDrawArrays(renderMode, 0, numVertexs);

    //Unlink Vao
    glBindVertexArray(0);
}

void Model::ApplyMatrix(Transform transform)
{
    //Define the translation, rotation and scaling matrix
    glm::mat4 translationMatrix = MatrixUtilities::GenerateTranslationMatrix(transform.position);
    glm::mat4 rotationMatrix = MatrixUtilities::GenerateRotationMatrix(transform.rotation, transform.rotation.x);
    rotationMatrix *= MatrixUtilities::GenerateRotationMatrix(transform.rotation, transform.rotation.y);
    rotationMatrix *= MatrixUtilities::GenerateRotationMatrix(transform.rotation, transform.rotation.z);
    glm::mat4 scaleMatrix = MatrixUtilities::GenerateScaleMatrix(transform.scale);

    //Assign initial values to the program
    glUniform2f(glGetUniformLocation(GetProgram(), "windowSize"), WINDOW_WIDTH, WINDOW_HEIGHT);

    //Pass the matrixs
    glUniformMatrix4fv(glGetUniformLocation(GetProgram(), "translationMatrix"), 1, GL_FALSE, glm::value_ptr(translationMatrix));
    glUniformMatrix4fv(glGetUniformLocation(GetProgram(), "rotationMatrix"), 1, GL_FALSE, glm::value_ptr(rotationMatrix));
    glUniformMatrix4fv(glGetUniformLocation(GetProgram(), "scaleMatrix"), 1, GL_FALSE, glm::value_ptr(scaleMatrix));
}

GLuint Model::GetProgram()
{
    return program;
}

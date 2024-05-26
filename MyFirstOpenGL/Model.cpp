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

void Model::Render()
{
    //Vinculo su VAO para ser usado
    glBindVertexArray(VAO);

    glUseProgram(program);

    if (texture != nullptr)
    {
        glUniform1i(glGetUniformLocation(program, "textureSampler"), texture->textureIndex);
    }

    // Dibujamos
    glDrawArrays(renderMode, 0, numVertexs);

    //Desvinculamos VAO
    glBindVertexArray(0);
}

GLuint Model::GetProgram()
{
    return program;
}

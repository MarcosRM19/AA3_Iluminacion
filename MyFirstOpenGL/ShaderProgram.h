#pragma once
#include <GL/glew.h>

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

class ShaderProgram
{
public:

	GLuint vertexShader;
	GLuint geometryShader;
	GLuint fragmentShader;

	ShaderProgram(std::string _vertexShader, std::string _geometryShader, std::string _fragmentShader);

	//Funcion que devolvera una string con todo el archivo leido
	std::string Load_File(const std::string& _filePath);

	GLuint LoadFragmentShader(const std::string& _filePath);
	GLuint LoadGeometryShader(const std::string& _filePath);
	GLuint LoadVertexShader(const std::string& _filePath);
};

//Función que dado un struct que contiene los shaders de un programa generara el programa entero de la GPU
GLuint CreateProgram(const ShaderProgram& shaders);


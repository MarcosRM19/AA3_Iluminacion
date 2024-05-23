#include "ProgramManager.h"

void ProgramManager::PushProgram(std::string _vShader, std::string _gShader, std::string _fShader)
{
	ShaderProgram program = ShaderProgram(_vShader, _gShader, _fShader);
	compiledPrograms.push_back(CreateProgram(program));
}

void ProgramManager::DeleteAllPrograms()
{
	for (int i = 0; i < compiledPrograms.size(); i++)
		glDeleteProgram(compiledPrograms[i]);
}


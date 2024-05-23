#pragma once
#include <GL/glew.h>
#include <vector>
#include <string>

#include "ShaderProgram.h"

#define PROGRAM_MANAGER ProgramManager::Instance()

class ProgramManager {
private:

	ProgramManager() = default;

	ProgramManager(const ProgramManager&) = delete;
	ProgramManager& operator =(const ProgramManager&) = delete;

public:

	inline static ProgramManager& Instance()
	{
		static ProgramManager programManager;
		return programManager;
	}

	std::vector<GLuint> compiledPrograms;

	void PushProgram(std::string _vShader, std::string _gShader, std::string _fShader);
	void DeleteAllPrograms();
};

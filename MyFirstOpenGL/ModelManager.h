#pragma once
#include <vector>
#include <sstream>
#include <fstream>
#include <glm.hpp>
#include <iostream>

#include "Model.h"

#define MODEL_MANAGER ModelManager::Instance()

class ModelManager {
private:

	ModelManager();

	ModelManager(const ModelManager&) = delete;
	ModelManager& operator =(const ModelManager&) = delete;

public:

	inline static ModelManager& Instance()
	{
		static ModelManager glManager;
		return glManager;
	}

	std::vector<Model> models;

	Model LoadOBJModel(const std::string& _filePath);
	Model LoadPrimitive(const std::vector<float>& _vertexs);
};



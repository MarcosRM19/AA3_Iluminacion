#pragma once
#include "GameObject.h"
#include "Camera.h"

#include "ModelManager.h"

#define OBJECT_MANAGER ObjectManager::Instance()

class ObjectManager
{
private:

	ObjectManager() = default;

	ObjectManager(const ObjectManager&) = delete;
	ObjectManager& operator =(const ObjectManager&) = delete;

public:

	inline static ObjectManager& Instance()
	{
		static ObjectManager objectManager;
		return objectManager;
	}
	~ObjectManager();

	Camera* camera;
	std::vector<glm::vec3*> spawnPoints;
	std::vector<GameObject*> gameObjects;

	void CreateSpwanPoint();
	void CreateObjects();

	void Update(float _dt);
};


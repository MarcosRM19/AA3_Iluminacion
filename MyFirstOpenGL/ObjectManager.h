#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "SpwanPoint.h"
#include "OrbitPrimitive.h"

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
	std::vector<SpawnPoint*> spawnPoints;
	std::vector<GameObject*> gameObjects;
	std::vector<OrbitPrimitive*> orbitPrimitive;

	void CreateSpwanPoint();
	void CreateObjects();

	void Update(float _dt);
};


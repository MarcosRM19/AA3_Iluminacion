#include "ObjectManager.h"

ObjectManager::~ObjectManager()
{
	delete camera;

	for (SpawnPoint* sPoint : spawnPoints)
		delete sPoint;

	for (GameObject* gObj : gameObjects)
		delete gObj;

	for (OrbitPrimitive* oPrimitive : orbitPrimitive)
		delete oPrimitive;
}

void ObjectManager::CreateSpwanPoint()
{
	spawnPoints.push_back(new SpawnPoint(Transform(glm::vec3(0.f, 0.f, 0.f))));
	spawnPoints.push_back(new SpawnPoint(Transform(glm::vec3(0.5f, 0.f, 0.f))));
	spawnPoints.push_back(new SpawnPoint(Transform(glm::vec3(-0.5f, 0.f, 0.f))));
}

void ObjectManager::CreateObjects()
{
	// 1. Set Camera
	camera = new Camera();

	std::vector<glm::vec3*> randomSpawnPoint;
	int randomIndex = rand() % spawnPoints.size();

	for (int i = 0; i < spawnPoints.size(); i++)
	{
		while (spawnPoints[randomIndex]->GetModelLocated())
		{
			randomIndex = rand() % spawnPoints.size();
		}		
		randomSpawnPoint.push_back(new glm::vec3(spawnPoints[randomIndex]->GetPosition()));
		spawnPoints[randomIndex]->SetModelLocated(true);
	}

	gameObjects.push_back(new GameObject(glm::vec3(randomSpawnPoint[0]->r, randomSpawnPoint[0]->g, randomSpawnPoint[0]->b), { 0.5f, 1.f, 0.5f, 1.f }, 0.1f, 0.3f, MODEL_MANAGER.models[0]));

	gameObjects.push_back(new GameObject(glm::vec3(randomSpawnPoint[1]->r, randomSpawnPoint[1]->g, randomSpawnPoint[1]->b), { 1.f, 0.5f, 0.5f, 1.f }, 0.1f, 0.3f, MODEL_MANAGER.models[0]));

	gameObjects.push_back(new GameObject(glm::vec3(randomSpawnPoint[2]->r, randomSpawnPoint[2]->g, randomSpawnPoint[2]->b), { 0.5f, 0.5f, 1.f, 1.f }, 0.1f, 0.3f, MODEL_MANAGER.models[0]));

	//Sun and Moon

	orbitPrimitive.push_back(new OrbitPrimitive({ 1.f, .6f, 0.f, 0.f }, MODEL_MANAGER.models[2], 0.f, 1.f, 20.f));

	orbitPrimitive.push_back(new OrbitPrimitive({ 0.1f, 0.3f, 0.4f, 0.f }, MODEL_MANAGER.models[2], M_PI, 1.f, 20.f));
}

void ObjectManager::Update(float _dt)
{
	camera->Update(_dt);
	camera->Inputs(GL_MANAGER.window, _dt);

	for (GameObject* gObj : gameObjects)
	{
		gObj->Update(_dt);
	}

	for (OrbitPrimitive* oPrimitive : orbitPrimitive)
	{
		oPrimitive->Update(_dt);
	}
}

#include "ObjectManager.h"

ObjectManager::~ObjectManager()
{
	delete camera;
	delete floor;

	for (glm::vec3* sPoint : spawnPoints)
		delete sPoint;

	for (GameObject* gObj : gameObjects)
		delete gObj;

	for (OrbitPrimitive* oPrimitive : orbitPrimitive)
		delete oPrimitive;
}

void ObjectManager::CreateSpwanPoint()
{
	//Create SpawnPoint
	spawnPoints.push_back(new glm::vec3(0.f, 0.f, 0.f));
	spawnPoints.push_back(new glm::vec3(0.5f, 0.f, 0.5f));
	spawnPoints.push_back(new glm::vec3(0.5f, 0.f, 0.f));
	spawnPoints.push_back(new glm::vec3(-0.5f, 0.f, 0.5f));
}

void ObjectManager::CreateObjects()
{
	//Set Camera
	camera = new Camera();

	floor = new Floor(glm::vec3(0.f, -1.9f, 0.f), MODEL_MANAGER.models[0]);

	//Set GameObjects with models
	gameObjects.push_back(new GameObject(GetRandomPosition(), 0.2f, 0.4f, MODEL_MANAGER.models[1]));

	gameObjects.push_back(new GameObject(GetRandomPosition(), 0.1f, 0.3f, MODEL_MANAGER.models[2]));

	gameObjects.push_back(new GameObject(GetRandomPosition(), 0.1f, 0.3f, MODEL_MANAGER.models[3]));

	gameObjects.push_back(new GameObject(GetRandomPosition(), 0.2f, 0.4f, MODEL_MANAGER.models[4]));

	//Set orbit objects 
	orbitPrimitive.push_back(new OrbitPrimitive({ 1.f, .6f, 0.f, 0.f }, MODEL_MANAGER.models[5], 0.f, 1.f, 20.f, 1, true));

	orbitPrimitive.push_back(new OrbitPrimitive({ 0.1f, 0.3f, 0.4f, 0.f }, MODEL_MANAGER.models[5], M_PI, 1.f, 20.f, 0.5, false));
}

void ObjectManager::Update(float _dt)
{
	camera->Update(_dt);
	camera->Inputs(GL_MANAGER.window, _dt);

	floor->Update(_dt);

	for (GameObject* gObj : gameObjects)
	{
		gObj->Update(_dt);
	}

	for (OrbitPrimitive* oPrimitive : orbitPrimitive)
	{
		oPrimitive->Update(_dt);
	}
}

glm::vec3 ObjectManager::GetRandomPosition()
{
	//Randomize the spawnpoints
	glm::vec3 randomPosition;
	int randomIndex = rand() % spawnPoints.size();

	randomPosition = glm::vec3(spawnPoints[randomIndex]->r, spawnPoints[randomIndex]->g, spawnPoints[randomIndex]->b);
	spawnPoints.erase(spawnPoints.begin() + randomIndex);

	return randomPosition;
}

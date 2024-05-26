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
	
	Texture* textureTroll = new Texture("Assets/Textures/Troll.png", GL_TEXTURE0, 0);

	gameObjects.push_back(new GameObject(PROGRAM_MANAGER.compiledPrograms[0],
		glm::vec3(randomSpawnPoint[0]->r, randomSpawnPoint[0]->g, randomSpawnPoint[0]->b),
		{ 0.5f, 1.f, 0.5f, 1.f },
		MODEL_MANAGER.models[0].GetVAO(), MODEL_MANAGER.models[0].GetNumVertexs(), textureTroll, GL_TRIANGLES, 0.1f, 0.3f));

	gameObjects.push_back(new GameObject(PROGRAM_MANAGER.compiledPrograms[0],
		glm::vec3(randomSpawnPoint[1]->r, randomSpawnPoint[1]->g, randomSpawnPoint[1]->b),
		{ 1.f, 0.5f, 0.5f, 1.f },
		MODEL_MANAGER.models[0].GetVAO(), MODEL_MANAGER.models[0].GetNumVertexs(), textureTroll, GL_TRIANGLES, 0.1f, 0.3f));

	gameObjects.push_back(new GameObject(PROGRAM_MANAGER.compiledPrograms[0],
		glm::vec3(randomSpawnPoint[2]->r, randomSpawnPoint[2]->g, randomSpawnPoint[2]->b),
		{ 0.5f, 0.5f, 1.f, 1.f },
		MODEL_MANAGER.models[0].GetVAO(), MODEL_MANAGER.models[0].GetNumVertexs(), textureTroll, GL_TRIANGLES, 0.1f, 0.3f));

	//Sun and Moon

	orbitPrimitive.push_back(new OrbitPrimitive(PROGRAM_MANAGER.compiledPrograms[1],
		glm::vec3(0.f, -1.f, 0.f),{ 1.f, .6f, 0.f, 0.f },
		MODEL_MANAGER.models[2].GetVAO(), MODEL_MANAGER.models[2].GetNumVertexs(), GL_TRIANGLE_STRIP, 0));

	orbitPrimitive.push_back(new OrbitPrimitive(PROGRAM_MANAGER.compiledPrograms[1],
		glm::vec3(0.f, 1.f, 0.f), { 0.1f, 0.3f, 0.4f, 0.f },
		MODEL_MANAGER.models[2].GetVAO(), MODEL_MANAGER.models[2].GetNumVertexs(), GL_TRIANGLE_STRIP, M_PI));
}

void ObjectManager::Update(float _dt)
{
	camera->Update(_dt);
	camera->Inputs(GL_MANAGER.window, _dt);

	for (GameObject* gObj : gameObjects)
	{
		gObj->Update(_dt);
		gObj->Render();
	}

	for (OrbitPrimitive* oPrimitive : orbitPrimitive)
	{
		oPrimitive->Update(_dt);
		oPrimitive->Render();
	}
}

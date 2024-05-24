#include "ObjectManager.h"

ObjectManager::~ObjectManager()
{
	delete camera;

	for (glm::vec3* sPoint : spawnPoints)
		delete sPoint;

	for (GameObject* gObj : gameObjects)
		delete gObj;
}

void ObjectManager::CreateSpwanPoint()
{
	spawnPoints.push_back(new glm::vec3(0.f, 0.f, 0.f));
	spawnPoints.push_back(new glm::vec3(0.5f, 0.f, 0.f));
	spawnPoints.push_back(new glm::vec3(-0.5f, 0.f, 0.f));

}

void ObjectManager::CreateObjects()
{
	// 1. Set Camera
	camera = new Camera();

	// 2. Set GaemObjects

	// TROLLS
	/*Texture* textureTroll = new Texture("Assets/Textures/Troll.png", GL_TEXTURE0, 0);

	gameObjects.push_back(new GameObject(PROGRAM_MANAGER.compiledPrograms[0],
		Transform(glm::vec3(0.f, 0.25f, 1.1f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.15f)),
		{ 0.5f, 1.f, 0.5f, 1.f },
		MODEL_MANAGER.models[0].GetVAO(), MODEL_MANAGER.models[0].GetNumVertexs(), textureTroll, GL_TRIANGLES));

	gameObjects.push_back(new GameObject(PROGRAM_MANAGER.compiledPrograms[0],
		Transform(glm::vec3(-0.2f, 0.25f, 1.3f), glm::vec3(0.f, 80., 0.f), glm::vec3(0.1f)),
		{ 1.f, 0.5f, 0.5f, 1.f },
		MODEL_MANAGER.models[0].GetVAO(), MODEL_MANAGER.models[0].GetNumVertexs(), textureTroll, GL_TRIANGLES));

	gameObjects.push_back(new GameObject(PROGRAM_MANAGER.compiledPrograms[0],
		Transform(glm::vec3(0.2f, 0.25f, 1.3f), glm::vec3(0.f, 280.f, 0.f), glm::vec3(0.1f)),
		{ 0.5f, 0.5f, 1.f, 1.f },
		MODEL_MANAGER.models[0].GetVAO(), MODEL_MANAGER.models[0].GetNumVertexs(), textureTroll, GL_TRIANGLES));

	// ROCKS
	Texture* textureRock = new Texture("Assets/Textures/Rock.png", GL_TEXTURE1, 1);

	gameObjects.push_back(new GameObject(PROGRAM_MANAGER.compiledPrograms[0],
		Transform(glm::vec3(0.0f, 0.25f, 1.2f), glm::vec3(0.f, 0.f, 270.f), glm::vec3(0.05f)),
		{ 0.9f, 0.9f, 0.9f, 1.f },
		MODEL_MANAGER.models[1].GetVAO(), MODEL_MANAGER.models[1].GetNumVertexs(), textureRock, GL_TRIANGLES));

	gameObjects.push_back(new GameObject(PROGRAM_MANAGER.compiledPrograms[0],
		Transform(glm::vec3(0.3f, 0.8f, 0.8f), glm::vec3(-10.f, 0.f, 270.f), glm::vec3(0.15f)),
		{ 0.3f, 0.3f, 0.3f, 1.f },
		MODEL_MANAGER.models[1].GetVAO(), MODEL_MANAGER.models[1].GetNumVertexs(), textureRock, GL_TRIANGLES));

	gameObjects.push_back(new GameObject(PROGRAM_MANAGER.compiledPrograms[0],
		Transform(glm::vec3(-0.3f, 0.8f, 0.8f), glm::vec3(10.f, 0.f, 270.f), glm::vec3(0.15f)),
		{ 0.3f, 0.3f, 0.3f, 1.f },
		MODEL_MANAGER.models[1].GetVAO(), MODEL_MANAGER.models[1].GetNumVertexs(), textureRock, GL_TRIANGLES));*/

	//// CUBE
	
	Texture* textureTroll = new Texture("Assets/Textures/Troll.png", GL_TEXTURE0, 0);

	gameObjects.push_back(new GameObject(PROGRAM_MANAGER.compiledPrograms[0],
		glm::vec3(spawnPoints[0]->r, spawnPoints[0]->g, spawnPoints[0]->b),
		{ 0.5f, 1.f, 0.5f, 1.f },
		MODEL_MANAGER.models[0].GetVAO(), MODEL_MANAGER.models[0].GetNumVertexs(), textureTroll, GL_TRIANGLES, 0.1f, 0.5f));

	gameObjects.push_back(new GameObject(PROGRAM_MANAGER.compiledPrograms[0],
		glm::vec3(spawnPoints[1]->r, spawnPoints[1]->g, spawnPoints[1]->b),
		{ 1.f, 0.5f, 0.5f, 1.f },
		MODEL_MANAGER.models[0].GetVAO(), MODEL_MANAGER.models[0].GetNumVertexs(), textureTroll, GL_TRIANGLES, 0.1f, 0.5f));

	gameObjects.push_back(new GameObject(PROGRAM_MANAGER.compiledPrograms[0],
		glm::vec3(spawnPoints[2]->r, spawnPoints[2]->g, spawnPoints[2]->b),
		{ 0.5f, 0.5f, 1.f, 1.f },
		MODEL_MANAGER.models[0].GetVAO(), MODEL_MANAGER.models[0].GetNumVertexs(), textureTroll, GL_TRIANGLES, 0.1f, 0.5f));
}

void ObjectManager::Update(float _dt)
{
	camera->Update(_dt);
	camera->Inputs(GL_MANAGER.window);

	for (GameObject* gObj : gameObjects)
	{
		gObj->Update(_dt);
		gObj->Render();
	}

}

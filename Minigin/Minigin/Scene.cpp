#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace Rius;

unsigned int Scene::m_IdCounter = 0;
std::vector<GameObject*> Rius::Scene::m_pObjects;
Scene::Scene(const std::string& name) : m_Name(name)
{
	UI::GetInstance().Initialize();
}


Scene::~Scene()
{
	for (int i{}; i < int(m_pObjects.size()); i++)
		delete m_pObjects[i];
}

void Scene::Add(GameObject* object)
{
	m_pObjects.push_back(object);
	for (auto& object : m_pObjects)
	{
		object->Initialize();
	}
}

void Scene::UpdateObjects()
{
	UI::GetInstance().Update();
	for (auto& object : m_pObjects)
	{
		object->Update();
	}
}

void Scene::LateUpdateObjects()
{
	for (auto& object : m_pObjects)
	{
		object->LateUpdate();
	}
}

void Scene::Render() const
{
	UI::GetInstance().Render();
	for (const auto& object : m_pObjects)
	{
		object->Render();
	}
}


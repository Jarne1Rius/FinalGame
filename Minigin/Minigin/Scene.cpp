#include "MiniginPCH.h"
#include "Scene.h"

#include "GameInstance.h"
#include "GameObject.h"

using namespace Rius;

unsigned int Scene::m_IdCounter = 0;
std::vector<GameObject*> Rius::Scene::m_pObjects;
Scene::Scene(const std::string& name) : m_Name(name), m_Pool(30)
{
	UI::GetInstance().Initialize();
}


Scene::~Scene()
{
	for (int i{}; i < int(m_pObjects.size()); i++)
		delete m_pObjects[i];
	delete m_pBackground;
}

void Scene::Remove()
{
	for (int i = 0; i < int(m_ReadyToRemove.size()); ++i)
	{
		auto it = std::find(m_pObjects.begin(), m_pObjects.end(), m_ReadyToRemove[i]);
		if (it != m_pObjects.end())
		{
			m_pObjects.erase(it);
			break;
		}
		//if (m_pBackground == m_ReadyToRemove[i]) delete m_ReadyToRemove[i];
		delete m_ReadyToRemove[i];
	}
	m_ReadyToRemove.clear();
}

void Scene::AddBackGround(GameObject* pBackground)
{
	m_pBackground = pBackground;
	m_pBackground->Initialize();
}

void Scene::Add(GameObject* object)
{
	m_pObjects.push_back(object);
	//for (auto& object : m_pObjects)
	{
		object->Initialize();
	}
}

void Scene::Remove(GameObject* object)
{
	object->SetActive(false);
	m_ReadyToRemove.push_back(object);
}

void Scene::UpdateObjects(float deltaT)
{
	for (int i = 0; i < int(m_pObjects.size()); ++i)
	{
		m_pObjects[i]->Update(deltaT);
	}
	Remove();
	UI::GetInstance().Update();
}

void Scene::LateUpdateObjects()
{
	for (auto& object : m_pObjects)
	{
		object->LateUpdate();
	}
	Remove();
}

void Scene::Render() const
{
	if (m_pBackground != nullptr) m_pBackground->Render();
	for (const auto& object : m_pObjects)
	{
		object->Render();
	}
	UI::GetInstance().Render();
}

void Scene::Initialize()
{
}


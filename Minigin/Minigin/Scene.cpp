#include "MiniginPCH.h"
#include "Scene.h"
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
	auto it = std::find(m_pObjects.begin(), m_pObjects.end(), object);
	m_pObjects.erase(it);
	delete object;
}

void Scene::UpdateObjects(float deltaT)
{
	for (int i = 0; i < int(m_pObjects.size()); ++i)
	{
		m_pObjects[i]->Update(deltaT);
	}
	//std::vector<std::future<void>> results;
	//const int size{ 10 };
	//GameObject* pUpdate[size];
	//for (int i = 0; i < m_pObjects.size(); ++i)
	//{
	//	if ((i % size == 0 && i != 0) || i == m_pObjects.size() - 1)
	//	{
	//		results.emplace_back(m_Pool.enqueue([&pUpdate, i]
	//			{
	//				for (int k = 0; k < (i % 10)+1; ++k)
	//				{
	//					pUpdate[k]->Update();
	//				}
	//			}));
	//		pUpdate[0] = m_pObjects[i];
	//	}
	//	else
	//	{
	//		pUpdate[i % size] = m_pObjects[i];
	//	}
	//}

	//for (auto&& result : results)
	//	result.get();
	UI::GetInstance().Update();
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
	for (const auto& object : m_pObjects)
	{
		object->Render();
	}
	UI::GetInstance().Render();
}

void Scene::Initialize()
{
}


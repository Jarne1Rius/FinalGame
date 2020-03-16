#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void Rius::SceneManager::Update()
{
	for(auto& scene : m_Scenes)
	{
		scene->Update();
	}
}

void Rius::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

Rius::Scene& Rius::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = new Scene(name);
	m_Scenes.push_back(scene);
	return *scene;
}

void Rius::SceneManager::AddScene(Scene* newScene)
{
	m_Scenes.push_back(newScene);
}

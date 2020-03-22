#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void Rius::SceneManager::Update()
{
	for(auto& scene : m_Scenes)
	{
		scene->Update();
		scene->UpdateObjects();
	}
}

void Rius::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}


void Rius::SceneManager::AddScene(Scene* newScene)
{
	m_Scenes.push_back(newScene);
}

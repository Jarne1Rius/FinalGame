#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

std::vector<Rius::Scene*> Rius::SceneManager::m_Scenes;
int Rius::SceneManager::m_ActiveScene = -1;
void Rius::SceneManager::Update()
{
	m_Scenes[m_ActiveScene]->Update();
	m_Scenes[m_ActiveScene]->UpdateObjects();

}

void Rius::SceneManager::Render()
{
	m_Scenes[m_ActiveScene]->Render();

}

void Rius::SceneManager::LateUpdate()
{
	m_Scenes[m_ActiveScene]->LateUpdateObjects();
}


void Rius::SceneManager::AddScene(Scene* newScene)
{
	m_ActiveScene = int(m_Scenes.size());
	m_Scenes.push_back(newScene);
}

Rius::Scene* Rius::SceneManager::GetCurrentScene()
{
	if (m_ActiveScene == -1)return nullptr;
	return m_Scenes[m_ActiveScene];
}

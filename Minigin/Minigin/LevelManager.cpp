#include "MiniginPCH.h"
#include "LevelManager.h"

#include "BoxCollider2D.h"
#include "LevelReader.h"
#include "TextureMaterial.h"
#include "GameObject.h"
#include "MaterialManager.h"
#include "Minigin.h"
#include "WallComponent.h"
#include "Scene.h"

#include "TextComponent.h"

Rius::Level::Level(std::vector<Rectangle2D> walls, int levelID, TextureMaterial* materialSmall, TextureMaterial* materialBig, std::string locationBigTexture, std::string locationSmallTexture)
	:m_StartPos({ 0,0 }), m_pBackGround(), m_Walls(walls), m_LevelID(), m_AI(), m_MaterialSmall(materialSmall), m_MaterialBig(materialBig), m_BigTexture(locationBigTexture), m_SmallTexture(locationSmallTexture)
{

}

void Rius::Level::Initialize()
{
}

void Rius::Level::StartLevel(GameObject* pPlayer)
{
	m_MaterialBig->SetTexture(m_BigTexture, "BackgroundBig", false);
	m_MaterialSmall->SetTexture(m_SmallTexture, "BackgroundSmall", false);
	float width = float(Minigin::m_Width);
	width /= 32.f;
	float height = float(Minigin::m_Height);
	height /= 27.f;
	m_pBackGround = new GameObject{};
	WallComponent* wall;
	BoxCollider2D* collider;
	for (int i = 0; i < int(m_Walls.size()); ++i)
	{
		wall = new WallComponent{ {0,0},m_MaterialSmall,m_Walls[i],width,height };
		collider = new BoxCollider2D(m_Walls[i]);
		collider->SetIgnoreGroups(Group3, true);
		collider->SetStatic(true);
		m_pBackGround->AddComponent(wall);
		m_pBackGround->AddComponent(collider);
	}
	wall = new WallComponent({ 0.f,0 }, m_MaterialBig, { 0,0,width * 2, float(Minigin::m_Height - height * 2) }, width, height);
	m_pBackGround->AddComponent(wall);
	wall = new WallComponent({ 0.f,0 }, m_MaterialBig, { float(Minigin::m_Width - width * 2),0,width * 2, float(Minigin::m_Height - height * 2) }, width, height);
	m_pBackGround->AddComponent(wall);
	TextComponent* ptext = new TextComponent{ std::to_string(m_LevelID + 1),{0,0,0},{0,height * 3} };
	m_pBackGround->AddComponent(ptext);
	m_pBackGround->SetActive(true);
	SceneManager::GetCurrentScene()->Add(m_pBackGround);
}

void Rius::Level::EndLevel()
{
	SceneManager::GetCurrentScene()->Remove(m_pBackGround);
}

void Rius::LevelManager::LoadLevels(const std::string& location, const std::string& locationsBigTextures, const std::string& locationSmallTextures, Scene* scene)
{
	TextureMaterial* mat2 = new TextureMaterial{ "Resources/BigBlocks/Big_02.gif", "Back0","BackgroundBig",false };
	TextureMaterial* mat3 = new TextureMaterial{ "Resources/SmallBlocks/small_02.png", "Back1","BackgroundSmall",false };
	MaterialManager::AddMaterial(mat2);
	MaterialManager::AddMaterial(mat3);
	std::vector<std::vector<Rectangle2D>> levels = LevelReader::ReadFromObjFile(location);
	for (int i = 0; i < int(levels.size()); ++i)
	{
		m_Levels.push_back(new Level{ levels[i],i,mat3,mat2,locationsBigTextures + ((i + 1 < 10) ? '0' + std::to_string((i + 1)) : std::to_string(i + 1)) + ".gif"
			,locationSmallTextures + ((i + 1 < 10) ? '0' +std::to_string(i + 1) : std::to_string(i + 1)) + ".png" });
	}

}

void Rius::LevelManager::SetLevel(int level, GameObject* pPlayer)
{
//	m_Levels[m_CurrentLevel]->EndLevel();
	m_CurrentLevel = level;
	m_Levels[m_CurrentLevel]->StartLevel(pPlayer);
}

void Rius::LevelManager::NextLevel(GameObject* pPlayer)
{
	m_Levels[m_CurrentLevel]->EndLevel();
	m_CurrentLevel++;
	m_Levels[m_CurrentLevel]->StartLevel(pPlayer);
}

void Rius::LevelManager::ResetLevel(GameObject* pPlayer)
{
	m_Levels[m_CurrentLevel]->StartLevel(pPlayer);
}

void Rius::LevelManager::QuitLevel()
{
	m_Levels[m_CurrentLevel]->EndLevel();
}

Rius::LevelManager::LevelManager()
{
}

Rius::LevelManager::~LevelManager()
{
	for (int i = 0; i < int(m_Levels.size()); ++i)
	{
		delete m_Levels[i];
	}
}

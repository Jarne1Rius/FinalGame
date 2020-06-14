#include "MiniginPCH.h"
#include "LevelManager.h"


#include "AI.h"
#include "BoxCollider2D.h"
#include "LevelReader.h"
#include "TextureMaterial.h"
#include "GameObject.h"
#include "MaterialManager.h"
#include "Minigin.h"
#include "WallComponent.h"
#include "Scene.h"

#include "TextComponent.h"

Rius::Level::Level(std::vector<Rectangle2D> walls, int levelID, TextureMaterial* materialSmall, TextureMaterial* materialBig, std::string locationBigTexture, std::string locationSmallTexture, const std::vector<glm::vec3>& posEnemies, const std::vector<glm::vec2>& startPos)
	:m_StartPos(startPos), m_pBackGround(), m_Walls(walls), m_LevelID(levelID), m_AI(posEnemies), m_MaterialSmall(materialSmall), m_MaterialBig(materialBig), m_BigTexture(locationBigTexture), m_SmallTexture(locationSmallTexture)
{

}

void Rius::Level::Initialize()
{
}

void Rius::Level::StartLevel(GameObject* pPlayer)
{
	pPlayer->GetTransform().SetPosition(glm::vec3(m_StartPos[0].x, -m_StartPos[0].y, 0));
	InitLevel();
}

void Rius::Level::StartLevel(std::vector<GameObject*> pPlayer)
{
	for (int i = 0; i < int(m_StartPos.size()); ++i)
	{
		if (int(pPlayer.size()) > i) {
			pPlayer[i]->GetTransform().SetPosition(glm::vec3(m_StartPos[i].x, -m_StartPos[i].y, 0));
			pPlayer[i]->SetPreviousPos(glm::vec3(m_StartPos[i].x, -m_StartPos[i].y, 0));
		}
	}
	InitLevel();
}

void Rius::Level::EndLevel()
{
	SceneManager::GetCurrentScene()->Remove(m_pBackGround);
}

void Rius::Level::SetPosition(GameObject* pPlayer, int id)
{
	pPlayer->GetTransform().SetPosition(glm::vec3(m_StartPos[id].x, -m_StartPos[id].y, 0));
}

void Rius::Level::CreateEnemy(const glm::vec3& pos)
{
	TextureMaterial* mat = new TextureMaterial{ "Resources/Enemy/Enemy.png", "Enemy" + std::to_string(MaterialManager::m_ID),"Enemy" + std::to_string(MaterialManager::m_ID),true };
	MaterialManager::AddMaterial(mat);
	GameObject* enemy = new GameObject{};
	std::vector<Animation>animations{
	{ ConvertToUVCoordinates({0,117,65,16},mat->GetTexture2D()), "Idle",1,0.2f,4,1,1},
	{ ConvertToUVCoordinates({238,117,74,16},mat->GetTexture2D()),"Death",4,0.4f,4,1,0},
	{ ConvertToUVCoordinates({0,117,70,16},mat->GetTexture2D()),"Running",4,0.2f,4,1,0},
	{ ConvertToUVCoordinates({ 0 ,0,634,37 }, mat->GetTexture2D()), "Food", 1, 0.2f, 35, 2, 1 }
	};
	SpriteSheetComponent* sprite = new SpriteSheetComponent(mat, Rectangle2D(0, 0, 50, 50), false, animations);
	enemy->AddComponent(new BoxCollider2D(Rectangle2D(0, 0, 45, 45), { 0.5f,0.5f }));
	enemy->SetTag(Tag::Enemy);
	enemy->AddComponent(new RigidBodyComponent{ 0.5f });
	Ai* ai = new Ai{ 1,{2,4},false ,3 };
	enemy->AddComponent(ai);
	enemy->AddComponent(sprite);
	enemy->GetTransform().Translate(pos);
	new MovingObjectObserver{ enemy };
	SceneManager::GetInstance().GetCurrentScene()->Add(enemy);
}

void Rius::Level::InitLevel()
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
	SceneManager::GetCurrentScene()->AddBackGround(m_pBackGround);

	for (auto ai : m_AI)
	{
		CreateEnemy(ai);
	}
	TextureMaterial* mat = new TextureMaterial{ "Resources/Enemy/Enemy.png", "Enemy" + std::to_string(MaterialManager::m_ID),"Enemy" + std::to_string(MaterialManager::m_ID),true };
	MaterialManager::AddMaterial(mat);
}
//levelmanager

void Rius::LevelManager::LoadLevels(const std::string& location, const std::string& locationsBigTextures, const std::string& locationSmallTextures, Scene*)
{
	TextureMaterial* mat2 = new TextureMaterial{ "Resources/BigBlocks/Big_02.gif", "Back0","BackgroundBig",false };
	TextureMaterial* mat3 = new TextureMaterial{ "Resources/SmallBlocks/small_02.png", "Back1","BackgroundSmall",false };
	MaterialManager::AddMaterial(mat2);
	MaterialManager::AddMaterial(mat3);
	std::vector<std::vector<Rectangle2D>> levels = LevelReader::ReadFromObjFile(location);
	std::vector<glm::vec3> enemies{ {90,420,0},{400,320,0} };
	for (int i = 0; i < int(levels.size()); ++i)
	{
		m_Levels.push_back(new Level{ levels[i],i,mat3,mat2,locationsBigTextures + ((i + 1 < 10) ? '0' + std::to_string((i + 1)) : std::to_string(i + 1)) + ".gif"
			,locationSmallTextures + ((i + 1 < 10) ? '0' + std::to_string(i + 1) : std::to_string(i + 1)) + ".png" ,enemies });
	}
}

void Rius::LevelManager::SetLevel(int level, GameObject* pPlayer)
{
	m_CurrentLevel = level;
	m_Levels[m_CurrentLevel]->StartLevel(pPlayer);
}

void Rius::LevelManager::NextLevel(GameObject* pPlayer)
{
	m_Levels[m_CurrentLevel]->EndLevel();
	m_CurrentLevel++;
	m_Levels[m_CurrentLevel]->StartLevel(pPlayer);
}

void Rius::LevelManager::NextLevel(std::vector<GameObject*> pPlayer)
{
	m_Levels[m_CurrentLevel]->EndLevel();
	m_CurrentLevel++;
	m_Levels[m_CurrentLevel]->StartLevel(pPlayer);
}

void Rius::LevelManager::ResetLevel(std::vector<GameObject*> pPlayer)
{
	m_Levels[m_CurrentLevel]->EndLevel();
	m_Levels[m_CurrentLevel]->StartLevel(pPlayer);
}

void Rius::LevelManager::ResetLevel(GameObject* pPlayer)
{
	m_Levels[m_CurrentLevel]->EndLevel();
	m_Levels[m_CurrentLevel]->StartLevel(pPlayer);
}

void Rius::LevelManager::QuitLevel()
{
	m_Levels[m_CurrentLevel]->EndLevel();
}

void Rius::LevelManager::SetPosition(GameObject* pPlayer, int id)
{
	m_Levels[m_CurrentLevel]->SetPosition(pPlayer, id);
}

Rius::LevelManager::LevelManager()
	:m_Levels(), m_CurrentLevel()
{
}

Rius::LevelManager::~LevelManager()
{
	for (int i = 0; i < int(m_Levels.size()); ++i)
	{
		delete m_Levels[i];
	}
}

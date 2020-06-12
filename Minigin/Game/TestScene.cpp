#include "TestScene.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include <glm/glm.hpp>

#include "TextMaterial.h"
#include "SpriteRenderer.h"
#include "SpriteSheetComponent.h"
#include "InputManager.h"
#include "RigidBodyComponent.h"
#include "Extra.h"
#include "ExtraMathFiles.h"
#include "BoxCollider2D.h"
#include "LevelReader.h"
#include "Minigin.h"
#include "UndoSystem.h"
#include "FiniteStateMachine.h"
#include "Logger.h"
#include "MaterialManager.h"
#include "TextureMaterial.h"
#include "HealthComponent.h"
#include "UI.h"
#include "WallComponent.h"
#include "LevelManager.h"
#include "AI.h"
#include "BulletPrefab.h"
#include "SpriteComponent.h"
#include "PlayerComponent.h"
using namespace Rius;
TestScene::TestScene()
	:Scene("TestScene")
{
	//Initialize();
}
void TestScene::Initialize()
{
	LevelManager::GetInstance().LoadLevels("Resources/FixedLevelData.dat", "Resources/BigBlocks/Big_", "Resources/SmallBlocks/small_", this);
	LevelManager::GetInstance().SetLevel(0, nullptr);
	//LevelManager::GetInstance().NextLevel(nullptr);
//
	TextureMaterial* mat = new TextureMaterial{ "Resources/awesomeface.png", "Sprite","Background",true };
	MaterialManager::AddMaterial(mat, 20);
	SpriteSheetComponent* sprite = new SpriteSheetComponent(mat, Rectangle2D(0, 0, 50, 50), false, 6, 4, 1);
	m_UI = new GameObject{};
	//TextMaterial* mat2 = new TextMaterial{ "Text",{1,0,0} };
	//HealthComponent* text = new HealthComponent{3,false};
	mat = new TextureMaterial{ "../Data/SpriteSheet.png", "Bullet","Bullet", true };
	MaterialManager::AddMaterial(mat);
	m_Rigid = new RigidBodyComponent(0.1f);
	BulletPrefab* bullet = new BulletPrefab{ mat,{415,1227,18,18} };
	bullet->GetTransform().Translate({ 100, 300,0 });
	PlayerComponent* playerComponent = new PlayerComponent{ 0,bullet };
//	m_UI->AddComponent(tes);
	//glm::vec2 force{ -0.1f,0 };
	m_UI->AddComponent(new BoxCollider2D(Rectangle2D(0, 0, 50, 50)));
	m_UI->AddComponent(m_Rigid);
	m_UI->AddComponent(playerComponent);
	m_UI->AddComponent(sprite);
	//m_UI->AddComponent(text);
	m_UI->GetTransform().SetPosition(100, 70, 0);

	Add(m_UI);

	GameObject* player1 = new GameObject();
	HealthComponent* pHealthComponent = new HealthComponent{ 2,true};
	
	Player p1;
	p1.pPlayer = m_UI;
	p1.m_Health = pHealthComponent;
	p1.m_color = { 1,0,0 };
	UI::GetInstance().AddPlayer(p1);
	//player1->AddComponent()
	//player1->GetTransform().Translate({100,-100, 0});
//	player1->AddComponent(pHealthComponent);
	player1->AddComponent(pHealthComponent);
	Add(player1);
	Add(bullet);
	GUISystem* system = new GUISystem(player1);

	GameObject* border = new GameObject{};
	border->SetTag(Tag::Ground);
	BoxCollider2D* box = new BoxCollider2D{ {-10,10,9,float(Minigin::m_Height - Minigin::m_TileHeight * 3)}, false, Group3 };
	box->SetStatic(true);
	border->AddComponent(box);
	box = new BoxCollider2D{ {float(Minigin::m_Width + 1),0,9,float(Minigin::m_Height - Minigin::m_TileHeight * 3)}, false, Group3 };
	box->SetStatic(true);
	border->AddComponent(box);
	box = new BoxCollider2D{ {0,-11,(float)Minigin::m_Width, 9}, false, Group3 };
	box->SetStatic(true);
	border->AddComponent(box);
	box = new BoxCollider2D{ {0,float(Minigin::m_Height + 10 - Minigin::m_TileHeight * 3),float(Minigin::m_Width),10}, false, Group3 };
	box->SetStatic(true);
	border->AddComponent(box);
	Add(border);
	mat = new TextureMaterial{ "Resources/awesomeface.png", "Sprite3","Background3",true };
	MaterialManager::AddMaterial(mat);
}

void TestScene::Update(float delatT)
{
	//InputManager::GetInstance().Test(m_UI);
	m_Angle += 0.0001f;
}

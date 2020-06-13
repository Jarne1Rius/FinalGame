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
#include "GameInstance.h"
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

	//LevelManager::GetInstance().NextLevel(nullptr);
//
	TextureMaterial* mat = new TextureMaterial{ "Resources/Players/GreenPlayer.png", "Sprite","Background",true };
	MaterialManager::AddMaterial(mat, 20);


	//Animation
	std::vector<Animation> animations{
		{ ConvertToUVCoordinates({0,80,142,-17},mat->GetTexture2D()),"Idle",1,0.2f,7,1,0},
		{ ConvertToUVCoordinates({142,80,168,-17},mat->GetTexture2D()),"Attack",8,0.05f,8,1,0},
		{ ConvertToUVCoordinates({166,3,144,-17},mat->GetTexture2D()),"Death",7,0.2f,7 ,1,0},
		{ ConvertToUVCoordinates({0,80,142,-17},mat->GetTexture2D()),"Running",7,0.2f,7,1,0}
	};

	SpriteSheetComponent* sprite = new SpriteSheetComponent(mat, Rectangle2D(0, 0, 50, 50), false, animations);
	//	SpriteSheetComponent* sprite = new SpriteSheetComponent(mat, Rectangle2D(0, 0, 50, 50), false, animations);
	m_Player = new GameObject{};
	//TextMaterial* mat2 = new TextMaterial{ "Text",{1,0,0} };
	//HealthComponent* text = new HealthComponent{3,false};
	mat = new TextureMaterial{ "../Data/SpriteSheet.png", "Bullet","Bullet", true };
	MaterialManager::AddMaterial(mat);
	m_Rigid = new RigidBodyComponent(0.5f);
	BulletPrefab* bullet = new BulletPrefab{ mat,{415,1227,18,18} };
	bullet->GetTransform().Translate({ 100, 300,0 });
	PlayerComponent* playerComponent = new PlayerComponent{ bullet };
	//	m_UI->AddComponent(tes);
		//glm::vec2 force{ -0.1f,0 };
	m_Player->SetTag(Tag::Player);
	m_Player->GetTransform().Scale({ -1,1,1 });
	m_Player->AddComponent(new BoxCollider2D(Rectangle2D(0, 0, 50, 50), { 0.5f,0.5f }));
	m_Player->GetComponent<BoxCollider2D>()->SetIgnoreGroups(Group2, true);
	m_Player->AddComponent(playerComponent);
	m_Player->AddComponent(m_Rigid);
	m_Player->AddComponent(sprite);
	m_Player->GetTransform().SetPosition(100, 70, 0);
	MovingObjectObserver* observer = new MovingObjectObserver{ m_Player };

	Add(m_Player);

	mat = new TextureMaterial{ "Resources/Enemy/Enemy.png", "Enemy","Enemy",true };
	MaterialManager::AddMaterial(mat, 21);
	animations = std::vector<Animation>{
		{ ConvertToUVCoordinates({0,131,65,-16},mat->GetTexture2D()), "Idle",1,0.2f,4,1,1},
		{ ConvertToUVCoordinates({238,131,74,-16},mat->GetTexture2D()),"Death",4,0.4f,4,1,0},
		{ ConvertToUVCoordinates({0,131,70,-16},mat->GetTexture2D()),"Running",4,0.2f,4,1,0},
		{ ConvertToUVCoordinates({ 0 ,37,634,-37 }, mat->GetTexture2D()), "Food", 1, 0.2f, 35, 2, 1 }

	};
	sprite = new SpriteSheetComponent(mat, Rectangle2D(0, 0, 50, 50), false, animations);
	GameObject* enemy = new GameObject{};
	enemy->AddComponent(new BoxCollider2D(Rectangle2D(0, 0, 50, 50), { 0.5f,0.5f }));
	enemy->SetTag(Tag::Interactions);
	//m_UI->GetComponent<BoxCollider2D>()->SetIgnoreGroups(Group2, true);
	m_Rigid = new RigidBodyComponent{ 1 };
	enemy->AddComponent(m_Rigid);
	Ai* ai = new Ai{ 1,{3,4},false };
	enemy->AddComponent(ai);
	//m_UI->AddComponent(playerComponent);
	enemy->AddComponent(sprite);
	enemy->GetTransform().Translate({ 500, 70 ,0 });
	//system = new GUISystem(enemy);
 observer = new MovingObjectObserver{ enemy };
	Add(enemy);

	GameObject* border = new GameObject{};
	border->SetTag(Tag::Ground);
	BoxCollider2D* box = new BoxCollider2D{ {-10,10,9,float(Minigin::m_Height - Minigin::m_TileHeight * 3)},{0,0}, false, Group3 };
	box->SetStatic(true);
	border->AddComponent(box);
	box = new BoxCollider2D{ {float(Minigin::m_Width + 1),0,9,float(Minigin::m_Height - Minigin::m_TileHeight * 3)},{0,0}, false, Group3 };
	box->SetStatic(true);
	border->AddComponent(box);
	box = new BoxCollider2D{ {0,-11,(float)Minigin::m_Width, 9},{0,0}, false, Group3 };
	box->SetStatic(true);
	border->AddComponent(box);
	box = new BoxCollider2D{ {0,float(Minigin::m_Height + 10 - Minigin::m_TileHeight * 3),float(Minigin::m_Width),10},{0,0}, false, Group3 };
	box->SetStatic(true);
	border->AddComponent(box);
	Add(border);
	mat = new TextureMaterial{ "Resources/awesomeface.png", "Sprite3","Background3",true };
	MaterialManager::AddMaterial(mat);
	LevelManager::GetInstance().SetLevel(0, m_Player);
}

void TestScene::Update(float delatT)
{
	//InputManager::GetInstance().Test(m_UI);
	m_Angle += 0.0001f;
}

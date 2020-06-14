#include "TestScene.h"
#include "GameObject.h"
#include "ResourceManager.h"

#include "SpriteRenderer.h"
#include "SpriteSheetComponent.h"
#include "InputManager.h"
#include "RigidBodyComponent.h"
#include "Extra.h"
#include "ExtraMathFiles.h"
#include "BoxCollider2D.h"
#include "LevelReader.h"
#include "Minigin.h"
#include "MaterialManager.h"
#include "TextureMaterial.h"
#include "LevelManager.h"
#include "BulletPrefab.h"
#include "PlayerComponent.h"
#include "ColliderEndScreen.h"
using namespace Rius;
TestScene::TestScene()
	:Scene("TestScene"),m_Rigid(),m_Player(),m_pBullet()
{
	//Initialize();
}

TestScene::~TestScene()
{
	delete m_pBullet;
}

void TestScene::Initialize()
{
	LevelManager::GetInstance().LoadLevels("Resources/FixedLevelData.dat", "Resources/BigBlocks/Big_", "Resources/SmallBlocks/small_", this);
	TextureMaterial* mat = new TextureMaterial{ "Resources/Enemy/Enemy.png", "Bullet","Bullet", true };
	m_pBullet = new BulletPrefab{ mat,{619,100,16,-16} };
	m_pBullet->GetTransform().Translate({ -100, -300,0 });

	//Player
	mat = new TextureMaterial{ "Resources/Players/GreenPlayer.png", "Sprite","Background",true };
	MaterialManager::AddMaterial(mat, 20);
	//Animation
	std::vector<Animation> animations{
		{ ConvertToUVCoordinates({0,63,142,17},mat->GetTexture2D()),"Idle",1,0.2f,7,1,0},
		{ ConvertToUVCoordinates({142,63,168,17},mat->GetTexture2D()),"Attack",8,0.05f,8,1,0},
		{ ConvertToUVCoordinates({166,-13,144,17},mat->GetTexture2D()),"Death",7,0.2f,7 ,1,0},
		{ ConvertToUVCoordinates({0,63,142,17},mat->GetTexture2D()),"Running",7,0.2f,7,1,0}
	};
	SpriteSheetComponent* sprite = new SpriteSheetComponent(mat, Rectangle2D(0, 0, 50, 50), false, animations);

	//P1
	m_Player = new GameObject{};
	m_Rigid = new RigidBodyComponent(0.5f);
	PlayerComponent* playerComponent = new PlayerComponent{ m_pBullet };
	m_Player->SetTag(Tag::Player);
	m_Player->GetTransform().Scale({ -1,1,1 });
	m_Player->AddComponent(new BoxCollider2D(Rectangle2D(0, 0, 50, 50), { 0.5f,0.5f }));
	m_Player->GetComponent<BoxCollider2D>()->SetIgnoreGroups(Group2, true);
	m_Player->AddComponent(playerComponent);
	m_Player->AddComponent(m_Rigid);
	m_Player->AddComponent(sprite);
	m_Player->GetTransform().SetPosition(-100, 70, 0);
	MovingObjectObserver* observer = new MovingObjectObserver{ m_Player };
	Add(m_Player);

	//p2
	mat = new TextureMaterial{ "Resources/Players/BluePlayer.png", "Sprite2","Background2",true };
	MaterialManager::AddMaterial(mat);
	sprite = new SpriteSheetComponent(mat, Rectangle2D(0, 0, 50, 50), false, animations);
	m_Player = new GameObject{};
	m_Rigid = new RigidBodyComponent(0.5f);
	playerComponent = new PlayerComponent{ m_pBullet };
	m_Player->SetTag(Tag::Player);
	m_Player->GetTransform().Scale({ -1,1,1 });
	m_Player->AddComponent(new BoxCollider2D(Rectangle2D(0, 0, 50, 50), { 0.5f,0.5f }));
	m_Player->GetComponent<BoxCollider2D>()->SetIgnoreGroups(Group2, true);
	m_Player->AddComponent(playerComponent);
	m_Player->AddComponent(m_Rigid);
	m_Player->AddComponent(sprite);
	m_Player->GetTransform().SetPosition(-400, 70, 0);
	observer = new MovingObjectObserver{ m_Player };
	Add(m_Player);

	ColliderEndScreen* endScreen = new ColliderEndScreen{ {0,-11,float(Minigin::m_Width), 9} ,{0,float(Minigin::m_Height + 10 - Minigin::m_TileHeight * 3),float(Minigin::m_Width),100} };
	Add(endScreen);
	
	GameObject* border = new GameObject{};
	border->SetTag(Tag::Ground);
	BoxCollider2D* box = new BoxCollider2D{ {-10,10,9,float(Minigin::m_Height - Minigin::m_TileHeight * 3)},{0,0}, false, Group3 };
	box->SetStatic(true);
	border->AddComponent(box);
	box = new BoxCollider2D{ {float(Minigin::m_Width + 1),0,9,float(Minigin::m_Height - Minigin::m_TileHeight * 3)},{0,0}, false, Group3 };
	box->SetStatic(true);
	border->AddComponent(box);
	Add(border);

	
	LevelManager::GetInstance().SetLevel(1, m_Player);

	mat = new TextureMaterial{ "Resources/Players/BluePlayer.png", "default","default",true };
	MaterialManager::AddMaterial(mat);
}

void TestScene::Update(float)
{
}

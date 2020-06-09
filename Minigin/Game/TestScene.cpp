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
#include "AI.h"
using namespace Rius;
TestScene::TestScene()
	:Scene("TestScene")
{
	Initialize();
}
UndoSystem systemm;
void TestScene::Initialize()
{
	TextureMaterial* mat = new TextureMaterial{ "Resources/awesomeface.png", "Sprite","Background",true };
	GameObject* p = new GameObject{};
	
	/*
	player1 = new GameObject();
	pHealthComponent = new HealthComponent{ 3,false };
	p1.pPlayer = player1;
	p1.m_Health = pHealthComponent;
	p1.m_color = { 0,0,1 };
	UI::GetInstance().AddPlayer(p1);
	player1->AddComponent(pHealthComponent);*/
//	Add(player1);
	//Init UI


	
	mat = new TextureMaterial{ "Resources/awesomeface.png", "Sprite","Background",true };
	MaterialManager::AddMaterial(mat, 20);
	SpriteSheetComponent* sprite = new SpriteSheetComponent(mat, Rectangle2D(0, 0, 50, 50), false, 6, 4, 1);
	m_UI = new GameObject{};
	//TextMaterial* mat2 = new TextMaterial{ "Text",{1,0,0} };
	//HealthComponent* text = new HealthComponent{3,false};
	m_Rigid = new RigidBodyComponent(0.1f);
	Ai* tes = new Ai{};
	m_UI->AddComponent(tes);
	//glm::vec2 force{ -0.1f,0 };
	m_UI->AddComponent(new BoxCollider2D(Rectangle2D(0, 0, 50, 50)));
	m_UI->AddComponent(m_Rigid);
	m_UI->AddComponent(sprite);
	//m_UI->AddComponent(text);
	m_UI->GetTransform().SetPosition(200, 300, 0);

	Add(m_UI);

	////m_Rigid->AddForce(force);
	////rigid->SetKinematic(true);
	LevelReader reader;
	std::vector<Rectangle2D> level = reader.ReadFromObjFile("Resources/FixedLevelData.dat")[10];
	WallComponent* obj;
	GameObject* ground = new GameObject();
	float width = float(Minigin::m_Width);
	width /= 32.f;
	float height = float(Minigin::m_Height);
	height /= 25.f;
	TextureMaterial* mat2 = new TextureMaterial{ "Resources/awesomeface.png", "Back","Background",true };
	for (Rectangle2D rectangle2D : level)
	{
		obj = new WallComponent(false, { 0,0 }, mat2, rectangle2D, width,height);
		BoxCollider2D* box = new BoxCollider2D(rectangle2D);
		box->SetStatic(true);
		ground->AddComponent(box);
		ground->AddComponent(obj);

		//obj->SetTexture(texture);
		//ground->GetTransform().SetPosition(640, 0, 0);
		ground->SetStatic(true);
	}
	Add(ground);


	GameObject* player1 = new GameObject();
	HealthComponent* pHealthComponent = new HealthComponent{ 2,true };
	Player p1;
	p1.pPlayer = player1;
	p1.m_Health = pHealthComponent;
	p1.m_color = { 1,0,0 };
	UI::GetInstance().AddPlayer(p1);
	player1->AddComponent(pHealthComponent);
	Add(player1);

	mat = new TextureMaterial{ "Resources/awesomeface.png", "Sprite","Background",true };
	//sprite = new SpriteSheetComponent(mat, Rectangle2D(0, 0, 50, 50), false, 6, 4, 1);
	//mat = new TextureMaterial{ "Resources/awesomeface.png", "Sprite","Background",true };
	//GameObject* test = new GameObject{};
	//test->AddComponent(sprite);
	//Add(test);

}

void TestScene::Update()
{
	//InputManager::GetInstance().Test(m_UI);
	m_Angle += 0.0001f;
}

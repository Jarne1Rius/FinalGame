#include "TestScene.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include "SpriteRendererComponent.h"
#include "SpriteSheetComponent.h"
#include "InputManager.h"
#include "Renderer.h"
#include "RigidBodyComponent.h"
#include "Extra.h"
#include "ExtraMathFiles.h"
#include "BoxCollider2D.h"
#include "LevelReader.h"
#include "Minigin.h"
#include "UndoSystem.h"
#include "FiniteStateMachine.h"
#include "Logger.h"
#include "TextureMaterial.h"
#include "PlayerComponent.h"
using namespace Rius;
TestScene::TestScene()
	:Scene("TestScene")
{
	Initialize();
}
UndoSystem systemm;
void TestScene::Initialize()
{
	
	m_UI = new GameObject();
	PlayerComponent* player {new PlayerComponent{0}};
	m_UI->AddComponent(player);
	/*int a{ 0 };
	bool b{ true };
	auto lambda = [this]()->bool { if (this->m_Angle == 1) std::cout << "test\n"; return this->m_Angle == 1; };

	m_Angle++;
	StateClass* running = new StateClass{};
	StateClass* ducking = new StateClass{};
	FiniteStateMachine* FSM = new FiniteStateMachine{ {running,ducking} };
	Transition* transition = new Transition{ lambda,running,ducking };
	transition = new Transition{ [&b]()->bool {if (b) std::cout << "test2\n"; return b; },ducking,running };
	FSM->UpdateState();
	FSM->UpdateState();
	for (int i = 0; i < 10; ++i)
	{
		FSM->UpdateState();
	}
	delete FSM;*/
	TextureMaterial* mat = new TextureMaterial{ "Resources/awesomeface.png", "Sprite","Background",true };

	SpriteSheetComponent* sprite = new SpriteSheetComponent(mat, Rectangle2D(0, 0, 50, 50), false, 6, 4, 1);

	m_Rigid = new RigidBodyComponent(0.1f);
	glm::vec2 force{ -0.1f,0 };
	m_UI->AddComponent(new BoxCollider2D(Rectangle2D(0, 0, 50, 50)));
	m_UI->AddComponent(m_Rigid);
	m_UI->AddComponent(sprite);
	m_UI->GetTransform().SetPosition(200, 600, 0);

	Add(m_UI);
	//m_Rigid->AddForce(force);
	//rigid->SetKinematic(true);
	LevelReader reader;
	std::vector<Rectangle2D> level = reader.ReadFromObjFile("Resources/FixedLevelData.dat")[10];
	SpriteRendererComponent* obj;
	GameObject* ground = new GameObject();
	float width = float(Minigin::m_Width);
	width /= 32.f;
	float height = float(Minigin::m_Height);
	height /= 25.f;
	TextureMaterial* mat2 = new TextureMaterial{ "Resources/awesomeface.png", "Back","Background",true };
	for (Rectangle2D rectangle2D : level)
	{
		obj = new SpriteRendererComponent(mat2, rectangle2D, width, height, true);
		BoxCollider2D* box = new BoxCollider2D(rectangle2D);
		box->SetStatic(true);
		ground->AddComponent(box);
		ground->AddComponent(obj);

		//obj->SetTexture(texture);
		//ground->GetTransform().SetPosition(640, 0, 0);
		ground->SetStatic(true);
	}
	Add(ground);

	


}

void TestScene::Update()
{
	InputManager::GetInstance().Test(m_UI);
	m_Angle += 0.0001f;
}

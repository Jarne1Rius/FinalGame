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
#include "UndoSystem.h"
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
	ResourceManager::LoadShader("Shader/SpriteTexture.vs", "Shader/SpriteTexture.fs", "Sprite");

	// to get the variables in fragmentshader
	ResourceManager::GetShader("Sprite")->Use().SetInt("image", 0);
	ResourceManager::GetShader("Sprite")->Use().SetBool("EnableTexture", true);
	ResourceManager::GetShader("Sprite")->SetMat4("projection", ResourceManager::m_ProjectionMatrix);
	Texture2D* texture = ResourceManager::LoadTexture("Resources/awesomeface.png", GL_TRUE, "BackGround");
	Shader* a = ResourceManager::GetShader("Sprite");
	
	SpriteSheetComponent* sprite = new SpriteSheetComponent(a, Rectangle2D(0, 0, 100, 100),6,4,1);
	//sprite->SetTexture(texture);
	sprite->SetColor(Color(0, 1, 0, 1));
	RigidBodyComponent* rigid = new RigidBodyComponent(0.1f);
	glm::vec2 force{ 0.1f,0 };
	rigid->AddForce(force);
	m_UI->AddComponent(new BoxCollider2D(Rectangle2D(0, 0, 100, 100)));
	m_UI->AddComponent(rigid);
	m_UI->AddComponent(sprite);
	m_UI->GetTransform().SetPosition(100, 400, 0);
	Add(m_UI);

	
	
	ResourceManager::LoadShader("Shader/SpriteTexture.vs", "Shader/SpriteTexture.fs", "Ground");
	ResourceManager::GetShader("Ground")->Use().SetInt("image", 0);
	ResourceManager::GetShader("Ground")->SetMat4("projection", ResourceManager::m_ProjectionMatrix);
	a = ResourceManager::GetShader("Ground");
	GameObject* ground = new GameObject();
	ground->AddComponent(new SpriteRendererComponent(a, Rectangle2D(400, 0, 800, 10)));
	ground->AddComponent(new BoxCollider2D(Rectangle2D(400, 0, 800, 10)));
	ground->GetComponent<SpriteRendererComponent>()->SetColor(Color(1, 0, 0, 1));
	Add(ground);
	Rius::InputManager::GetInstance().ChangeKey(Rius::KeyFunctions::Jump, Rius::ControllerButton::ButtonA);
	Rius::InputManager::GetInstance().ChangeKey(Rius::KeyFunctions::Left, Rius::ControllerButton::LeftStick);
	
}

void TestScene::Update()
{
	m_Angle += 0.0001f;
}

#include "TestScene.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include "SpriteRenderer.h"
#include "InputManager.h"
#include "Renderer.h"
#include "Extra.h"

TestScene::TestScene()
	:Scene("TestScene")
{
	Initialize();
}

void TestScene::Initialize()
{
	/*Rius::Renderer::GetInstance().Init(800, 600);
	Rius::ResourceManager::GetInstance().LoadShader("Shader/SpriteTexture.vs", "Shader/SpriteTexture.fs", "Sprite");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(800), static_cast<GLfloat>(600), 0.0f, -1.0f, 1.0f);
	Rius::ResourceManager::GetInstance().GetShader("Sprite")->Use().SetInt("image", 0);
	Rius::ResourceManager::GetInstance().GetShader("Sprite")->Use().SetVec3("spriteColor", 0, 1, 1);
	Rius::ResourceManager::GetInstance().GetShader("Sprite")->SetMat4("projection", projection);

	Rius::Texture2D* texture  =Rius::ResourceManager::GetInstance().LoadTexture("Resources/awesomeface.png", GL_FALSE, "BackGround");
	Rius::Shader* a = Rius::ResourceManager::GetInstance().GetShader("Sprite");

	Rius::SpriteRenderer* sprite = new Rius::SpriteRenderer(a, Rius::Rectangle2D(0, 0, 1, 1), Rius::Rectangle2D(0, 0, 1, 1));*/
	/*m_UI = new Rius::GameObject();
	m_UI->AddComponent(sprite);
	sprite->SetTexture(texture);
	Add(m_UI);*/
	
	Rius::InputManager::GetInstance().ChangeKey(Rius::KeyFunctions::Jump, Rius::ControllerButton::ButtonA);
	Rius::InputManager::GetInstance().ChangeKey(Rius::KeyFunctions::Left, Rius::ControllerButton::LeftStick);
	Rius::InputManager::GetInstance().SetRumble(1, 1);
}

void TestScene::Update()
{
	m_Angle += 0.0001f;
	//m_UI->GetTransform().Rotate(glm::radians(m_Angle), glm::vec3(0, 0, 1));
	//std::cout << Rius::InputManager::GetInstance().IsPressed(KeyFunctions::Jump) << "\n";
	//std::cout << Rius::InputManager::GetInstance().GetAxisGamePad(Rius::KeyFunctions::Left).x << "\n";
	
}

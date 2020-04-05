#include "TestScene.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "TextureComponent.h"
#include <glm/glm.hpp>

#include "TextComponent.h"
#include "Time.h"
#include "InputManager.h"


TestScene::TestScene()
	:Scene("TestScene")
{
	Initialize();
}

void TestScene::Initialize()
{

	auto ui = new Rius::GameObject();
	Rius::Font* font = Rius::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	Rius::TextureComponent* texture = new Rius::TextureComponent("background.jpg");
	ui->AddComponent(texture);
	Rius::TextComponent* text = new Rius::TextComponent("Programming 4 Assignment", font, glm::vec2{ 80,20 });
	ui->AddComponent(text);
	font = Rius::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	m_pFPSComponent = new Rius::FPSComponent(font);
	ui->AddComponent(m_pFPSComponent);
	texture = new Rius::TextureComponent("logo.png", glm::vec2{ 216,180 });
	ui->AddComponent(texture);
	ui->SetPosition(0, 0);
	Add(ui);
	Rius::InputManager::GetInstance().ChangeKey(KeyFunctions::Jump, Rius::ControllerButton::ButtonA);
	Rius::InputManager::GetInstance().ChangeKey(KeyFunctions::Left, Rius::ControllerButton::LeftStick);
	Rius::InputManager::GetInstance().SetRumble(1, 1);
}

void TestScene::Update()
{
	
	//std::cout << Rius::InputManager::GetInstance().IsPressed(KeyFunctions::Jump) << "\n";
	std::cout << Rius::InputManager::GetInstance().GetAxisGamePad(KeyFunctions::Left).x << "\n";
	
}

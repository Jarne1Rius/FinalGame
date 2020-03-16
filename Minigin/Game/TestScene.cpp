#include "TestScene.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "TextureComponent.h"
#include <glm/glm.hpp>


TestScene::TestScene()
{
	m_pScene = new Rius::Scene("TestScene");
	Initialize();
}

void TestScene::Initialize()
{

	auto go = new Rius::GameObject();
	//go->SetTexture("background.jpg");
	m_pScene->Add(go);

	go = new Rius::GameObject();
	//go->SetTexture("logo.png");
	go->SetPosition(216, 180);
	m_pScene->Add(go);

	auto ui = new Rius::GameObject();
	Rius::Font* font = Rius::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	Rius::TextureComponent* texture = new Rius::TextureComponent("background.jpg");
	ui->AddComponent(texture);
	Rius::TextComponent* text = new Rius::TextComponent("Programming 4 Assignment", font, glm::vec2{ 80,20 });
	ui->AddComponent(text);
	texture = new Rius::TextureComponent("logo.png", glm::vec2{ 216,180 });
	ui->AddComponent(texture);
	ui->SetPosition(0, 0);
	m_pScene->Add(ui);
}

void TestScene::Update()
{
}

void TestScene::Render() const
{
}

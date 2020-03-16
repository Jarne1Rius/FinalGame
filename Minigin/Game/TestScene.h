#pragma once
#include "Scene.h"
#include  "TextComponent.h"

class TestScene
{
public:
	TestScene();
	~TestScene() = default;
	void Update();
	void Render()const;
	Rius::Scene* GetScene() { return m_pScene; }
private:
	void Initialize();
	Rius::Scene* m_pScene;
	Rius::TextComponent* m_TextComponent;
};


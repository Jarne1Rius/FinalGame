#pragma once
#pragma once
#include "Scene.h"
#include  "FPSComponent.h"
#include "RigidBodyComponent.h"
#include "TextRenderer.h"

class TestScene : public Rius::Scene
{
public:
	TestScene();
	void Update() override;
	//void Render() const override;
private:
	void Initialize();
	Rius::RigidBodyComponent* m_Rigid;
	Rius::GameObject* m_UI;
	float m_Angle = 0;
	Rius::TextRenderer* text;
};


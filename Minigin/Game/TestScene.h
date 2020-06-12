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
	void Update(float deltaT) override;
	//void Render() const override;
private:
	void Initialize() override;
	Rius::RigidBodyComponent* m_Rigid;
	Rius::GameObject* m_UI;
	float m_Angle = 0;
	Rius::TextRenderer* text;
};


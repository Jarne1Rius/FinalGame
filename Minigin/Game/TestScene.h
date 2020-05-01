#pragma once
#include "Scene.h"
#include  "FPSComponent.h"
#include "RigidBodyComponent.h"

class TestScene : public Rius::Scene
{
public:
	TestScene();
	void Update() override;
private:
	void Initialize();
	Rius::RigidBodyComponent* m_Rigid;
	Rius::GameObject* m_UI;
	float m_Angle = 0;
};


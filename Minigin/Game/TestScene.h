#pragma once
#include "Scene.h"
#include  "FPSComponent.h"

class TestScene : public Rius::Scene
{
public:
	TestScene();
	void Update() override;
private:
	void Initialize();
	Rius::FPSComponent* m_pFPSComponent;
};


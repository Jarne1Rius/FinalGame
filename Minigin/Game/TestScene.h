#pragma once
#include "Scene.h"
#include  "FPSComponent.h"

class TestScene : public Rius::Scene
{
public:
	TestScene();
	~TestScene() = default;
	void Update();
private:
	void Initialize();
	Rius::FPSComponent* m_pFPSComponent;
};


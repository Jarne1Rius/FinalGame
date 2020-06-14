#pragma once

#include "BulletPrefab.h"
#include "Scene.h"
#include "RigidBodyComponent.h"

class TestScene : public Rius::Scene
{
public:
	TestScene();
	~TestScene();
	void Update(float deltaT) override;
	//void Render() const override;
private:
	void Initialize() override;
	Rius::BulletPrefab* m_pBullet;
	Rius::RigidBodyComponent* m_Rigid;
	Rius::GameObject* m_Player;
};


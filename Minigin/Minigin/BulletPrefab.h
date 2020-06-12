#pragma once
#include "GameObject.h"
#include "SpriteComponent.h"

namespace Rius
{
	class BulletPrefab : public GameObject
	{
	public:
		explicit BulletPrefab(TextureMaterial* mat, const Rectangle2D& texCoordSizeOfTexture);
		~BulletPrefab();
		GameObject* Clone() override;
		void Update(float deltaT) override;
		void OnCollisionEnter(Collider* other) override;
	private:
		GameObject* m_pBullet;
		SpriteComponent* m_Sprite;
		RigidBodyComponent* m_pRigid;
		TextureMaterial* m_pMat;
		float m_Sec;
		float m_DurationBeforeHit;
	};

}

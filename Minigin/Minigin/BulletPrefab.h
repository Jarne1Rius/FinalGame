#pragma once
#include "GameObject.h"
#include "SpriteComponent.h"

namespace Rius
{
	class BulletPrefab : public GameObject
	{
	public:
		BulletPrefab(TextureMaterial* mat, const Rectangle2D& texCoordSizeOfTexture);
		~BulletPrefab();
		GameObject* Clone() override;
		void LateUpdate() override;
		void Update(float deltaT) override;
		void OnTriggerEnter(Collider* other) override;
	private:
		Rectangle2D m_TexCoordSizeOfTexture;
		SpriteComponent* m_Sprite;
		TextureMaterial* m_pMat;
		Collider* m_pCollider;
		float m_Sec;
		float m_DurationBeforeHit;
	};

}

#pragma once
#include "GameObject.h"
#include "SpriteComponent.h"

namespace Rius
{
	class Bullet 
	{
	public:
		explicit Bullet(TextureMaterial* mat, const Rectangle2D& texCoordSizeOfTexture);
		~Bullet();
		GameObject* Clone();
	private:
		GameObject* m_pBullet;
		SpriteComponent* m_Sprite;
		RigidBodyComponent* m_pRigid;
		TextureMaterial* m_pMat;
	};

}

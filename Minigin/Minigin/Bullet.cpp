#include "MiniginPCH.h"
#include "Bullet.h"
#include "RigidBodyComponent.h"

Rius::Bullet::Bullet(TextureMaterial* mat, const Rectangle2D& texCoordSizeOfTexture)
{
	m_Sprite = new SpriteComponent{mat,texCoordSizeOfTexture};
	m_pRigid = new RigidBodyComponent{1};
}

Rius::Bullet::~Bullet()
{
	delete m_pRigid;
	delete m_Sprite;
}

Rius::GameObject* Rius::Bullet::Clone()
{
	GameObject* obj = new GameObject{};
	obj->AddComponent(m_Sprite->Clone());
	obj->AddComponent(m_pRigid->Clone());
	return obj;
}

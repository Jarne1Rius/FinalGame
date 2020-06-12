#include "MiniginPCH.h"
#include "BulletPrefab.h"
#include "RigidBodyComponent.h"

Rius::BulletPrefab::BulletPrefab(TextureMaterial* mat, const Rectangle2D& texCoordSizeOfTexture)
{
	m_Sprite = new SpriteComponent{mat,texCoordSizeOfTexture};
	m_pRigid = new RigidBodyComponent{1};
}

Rius::BulletPrefab::~BulletPrefab()
{
	delete m_pRigid;
	delete m_Sprite;
}

Rius::GameObject* Rius::BulletPrefab::Clone()
{
	BulletPrefab* obj = new BulletPrefab{m_pMat,{}};
	obj->AddComponent(m_Sprite->Clone());
	obj->AddComponent(m_pRigid->Clone());
	return obj;
}

void Rius::BulletPrefab::Update(float deltaT)
{
	m_Sec += deltaT;
	GameObject::Update(deltaT);
}

void Rius::BulletPrefab::OnCollisionEnter(Collider* other)
{
	GameObject::OnCollisionEnter(other);
}

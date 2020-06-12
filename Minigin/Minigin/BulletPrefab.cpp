#include "MiniginPCH.h"
#include "BulletPrefab.h"
#include "RigidBodyComponent.h"
#include "SceneManager.h"
#include "TextureMaterial.h"
#include "Scene.h"
#include "Time.h"

Rius::BulletPrefab::BulletPrefab(TextureMaterial* mat, const Rectangle2D& texCoordSizeOfTexture)
	:m_pMat(mat), m_TexCoordSizeOfTexture(texCoordSizeOfTexture), m_Sec(0)
{
	m_Sprite = new SpriteComponent{ mat,texCoordSizeOfTexture,30};
	m_pRigidBodyComponent = new RigidBodyComponent{ 1 };
	m_pRigidBodyComponent->SetKinematic(true);
	AddComponent(m_Sprite);
	AddComponent(m_pRigidBodyComponent);
}


Rius::BulletPrefab::~BulletPrefab()
{
	//delete m_pRigidBodyComponent;
	//delete m_Sprite;
}

Rius::GameObject* Rius::BulletPrefab::Clone()
{
	TextureMaterial* mat = new TextureMaterial{ *m_pMat };
	BulletPrefab* obj = new BulletPrefab{ mat,m_TexCoordSizeOfTexture };
	return obj;
}

void Rius::BulletPrefab::LateUpdate()
{
	m_Sec += (Time::m_DeltaTime);
	
	if (m_Sec > 3)
	{
		delete m_pMat;
		SceneManager::GetInstance().GetCurrentScene()->Remove(this);
	}
	else if (m_Sec > 2)
	{
		m_pRigidBodyComponent->SetForce(glm::vec3{ 0,-0.1f,0 });
	}
}

void Rius::BulletPrefab::Update(float deltaT)
{
	GameObject::Update(deltaT);
}

void Rius::BulletPrefab::OnCollisionEnter(Collider* other)
{
	GameObject::OnCollisionEnter(other);
}

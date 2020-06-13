#include "MiniginPCH.h"
#include "BulletPrefab.h"


#include "AI.h"
#include "BoxCollider2D.h"
#include "RigidBodyComponent.h"
#include "SceneManager.h"
#include "TextureMaterial.h"
#include "Scene.h"
#include "Time.h"

Rius::BulletPrefab::BulletPrefab(TextureMaterial* mat, const Rectangle2D& texCoordSizeOfTexture)
	:m_pMat(mat), m_TexCoordSizeOfTexture(texCoordSizeOfTexture), m_Sec(0),m_pCollider(),m_Sprite(),m_DurationBeforeHit()
{
	m_Sprite = new SpriteComponent{ mat,texCoordSizeOfTexture,30};
	m_pRigidBodyComponent = new RigidBodyComponent{ 1 };
	m_pRigidBodyComponent->SetKinematic(true);
	m_pCollider = new BoxCollider2D{ {0,0,30,30},{0,0},true, CollisionGroup::Group2 };
	AddComponent(m_Sprite);
	AddComponent(m_pCollider);
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
	
}

void Rius::BulletPrefab::Update(float deltaT)
{
	m_Sec += deltaT;
	if (m_Sec > 3)
	{
		delete m_pMat;
		SceneManager::GetInstance().GetCurrentScene()->Remove(this);
	}
	else if (m_Sec > 2)
	{
		m_pRigidBodyComponent->SetForce(glm::vec3{ 0,-20.1f,0 });
	}
	GameObject::Update(deltaT);
}

void Rius::BulletPrefab::OnTriggerEnter(Collider* other)
{
	if(other->GetGameObject()->GetTag() == Tag::Interactions)
	{
		other->GetGameObject()->GetComponent<Ai>()->DoDamage();
		//delete m_pMat;
		SceneManager::GetInstance().GetCurrentScene()->Remove(this);
	}
	GameObject::OnTriggerEnter(other);
}

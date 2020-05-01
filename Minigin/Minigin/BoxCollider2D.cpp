#include "MiniginPCH.h"
#include "BoxCollider2D.h"
#include "Extra.h"
#include "CircleCollider2D.h"
#include "GameObject.h"
#include "ExtraMathFiles.h"
#include "RigidBodyComponent.h"

Rius::BoxCollider2D::BoxCollider2D(Rectangle2D rectangle, bool isTrigger)
	:Collider(isTrigger),m_Rectangle(rectangle)
{
}

Rius::BoxCollider2D::~BoxCollider2D()
{
}

Rius::BoxCollider2D::BoxCollider2D(const BoxCollider2D& other)
	: Collider(other.m_Trigger), m_Rectangle(0,0,0,0)
{
	this->m_CollidersInCollision = other.m_CollidersInCollision;
	this->m_pGameObject = other.m_pGameObject;
	this->m_PreviousPos = other.m_PreviousPos;
	this->m_Trigger = other.m_Trigger;
	this->m_Rectangle = other.m_Rectangle;
}

void Rius::BoxCollider2D::Initialize()
{
	
}

void Rius::BoxCollider2D::Update()
{
	if(!m_Static)
		m_Rectangle.pos = m_pGameObject->GetTransform().GetPosition();
	m_Rectangle.pos.y *= -1;
	bool anyHit{false};
	if (this->m_Static) return;
	for (Collider* collider : m_AllColliders)
	{
		if (collider == this) continue;
		//if(collider->GetStatic() == true)continue;
		bool newHit = collider->CheckCollision(this);
		if(newHit)
		{
			if (m_Trigger) OnTriggerEnter(collider);
			
			else OnCollisionEnter(collider);
		}
		//std::map<Collider*, bool>::iterator it = m_CollidersInCollision.find(collider);
		//bool hit = it->second;
		//if (newHit != hit && hit)
		//{
		//	//exit collider
		//	if (m_Trigger) OnTriggerExit(collider);
		//	else OnCollisionExit(collider);
		//}
		//else if (newHit == hit && hit)
		//{
		//	//exit collider
		//	if (m_Trigger) OnTriggerStay(collider);
		//	else OnCollisionStay(collider);
		//}
		//else if (newHit != hit && hit == false)
		//{
		//	//exit collider
		//	if (m_Trigger) OnTriggerEnter(collider);
		//	else OnCollisionEnter(collider);
		//}
		//else
		//{
		//	continue;
		//}
		//if (newHit) anyHit = newHit;
		//it->second = newHit;
	}
	if (anyHit) GetGameObject()->GetTransform().SetPosition(m_PreviousPos);
	m_PreviousPos = GetGameObject()->GetTransform().GetPosition();
}

void Rius::BoxCollider2D::Render() const
{
}

glm::vec2 Rius::BoxCollider2D::GetCenter()
{
	return m_Rectangle.pos;
}

bool Rius::BoxCollider2D::CheckCollision(CircleCollider2D* circle)
{
	return Collision(this->m_Rectangle, circle->GetCircle2D());
}

bool Rius::BoxCollider2D::CheckCollision(BoxCollider2D* collider)
{
	glm::vec3 vel{ 0,0,0 };
	RigidBodyComponent* com = collider->m_pGameObject->GetRigidBodyComponent();
	if(com)
		return Collision(this->m_Rectangle, collider->m_Rectangle,vel, com->GetVelocity());
	else
		return Collision(this->m_Rectangle, collider->m_Rectangle, vel, vel);
}

bool Rius::BoxCollider2D::CheckCollision(CircleCollider3D* circle)
{
	return false;
}

bool Rius::BoxCollider2D::CheckCollision(BoxCollider3D* collider)
{
	return false;
}

Rius::BaseComponent* Rius::BoxCollider2D::Clone()
{
	return  new BoxCollider2D{ *this };
}

void Rius::BoxCollider2D::SetComponent(BaseComponent* comp)
{
	BoxCollider2D* component = static_cast<BoxCollider2D*>(comp);
	this->m_CollidersInCollision = component->m_CollidersInCollision;
	this->m_pGameObject = component->m_pGameObject;
	this->m_PreviousPos = component->m_PreviousPos;
	this->m_Trigger = component->m_Trigger;
	this->m_Rectangle = component->m_Rectangle;
}

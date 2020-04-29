#include "MiniginPCH.h"
#include "BoxCollider3D.h"
#include "CircleCollider3D.h"
#include "ExtraMathFiles.h"

Rius::BoxCollider3D::BoxCollider3D(Rectangle3D rectangle, bool isTrigger)
	:Collider(isTrigger)
{
}

Rius::BoxCollider3D::~BoxCollider3D()
{
}

Rius::BoxCollider3D::BoxCollider3D(const BoxCollider3D& other)
	: Collider(other.m_Trigger), m_Rectangle()
{
	this->m_CollidersInCollision = other.m_CollidersInCollision;
	this->m_pGameObject = other.m_pGameObject;
	this->m_PreviousPos = other.m_PreviousPos;
	this->m_Trigger = other.m_Trigger;
	this->m_Rectangle = other.m_Rectangle;
}

Rius::BaseComponent* Rius::BoxCollider3D::Clone()
{
	return new BoxCollider3D{ *this };
}

void Rius::BoxCollider3D::SetComponent(BaseComponent* comp)
{
	BoxCollider3D* component = static_cast<BoxCollider3D*>(comp);
	this->m_CollidersInCollision = component->m_CollidersInCollision;
	this->m_pGameObject = component->m_pGameObject;
	this->m_PreviousPos = component->m_PreviousPos;
	this->m_Trigger = component->m_Trigger;
	this->m_Rectangle = component->m_Rectangle;
}

void Rius::BoxCollider3D::Initialize()
{
}

void Rius::BoxCollider3D::Update()
{
	for (Collider* collider : m_AllColliders)
	{
		bool newHit = collider->CheckCollision(this);
		std::map<Collider*, bool>::iterator it = m_CollidersInCollision.find(collider);
		bool hit = it->second;
		if (newHit != hit && hit)
		{
			//exit collider
			if (m_Trigger) OnTriggerExit(collider);
			else OnCollisionExit(collider);
		}
		else if (newHit == hit && hit)
		{
			//Stay collider
			if (m_Trigger) OnTriggerStay(collider);
			else OnCollisionStay(collider);
		}
		else if (newHit != hit && hit == false)
		{
			//Enter collider
			if (m_Trigger) OnTriggerEnter(collider);
			else OnCollisionEnter(collider);
		}
		else
		{
			continue;
		}

		it->second = newHit;
	}
}

void Rius::BoxCollider3D::Render() const
{
}

bool Rius::BoxCollider3D::CheckCollision(CircleCollider2D* circle)
{
	std::cout << "Error => 3D collider tries to collide with a 2D collider\n";
	return false;
}

bool Rius::BoxCollider3D::CheckCollision(BoxCollider2D* collider)
{
	std::cout << "Error => 3D collider tries to collide with a 2D collider\n";
	return false;
}

bool Rius::BoxCollider3D::CheckCollision(CircleCollider3D* circle)
{
	return Collision(this->m_Rectangle, circle->GetCircle3D());
}

bool Rius::BoxCollider3D::CheckCollision(BoxCollider3D* collider)
{
	return Collision(this->m_Rectangle, collider->m_Rectangle);
}

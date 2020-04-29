#include "MiniginPCH.h"
#include "CircleCollider2D.h"
#include  "ExtraMathFiles.h"
#include "BoxCollider2D.h"
#include <iostream>
Rius::CircleCollider2D::CircleCollider2D(Circle2D circle, bool isTrigger)
	:Collider(isTrigger), m_Circle2D(circle)
{
}

Rius::CircleCollider2D::~CircleCollider2D()
{
}

Rius::CircleCollider2D::CircleCollider2D(const CircleCollider2D& other)
	: Collider(other.m_Trigger)
{
	this->m_CollidersInCollision = other.m_CollidersInCollision;
	this->m_pGameObject = other.m_pGameObject;
	this->m_PreviousPos = other.m_PreviousPos;
	this->m_Trigger = other.m_Trigger;
	this->m_Circle2D = other.m_Circle2D;
}

void Rius::CircleCollider2D::Initialize()
{
}

void Rius::CircleCollider2D::Update()
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

void Rius::CircleCollider2D::Render() const
{
}

bool Rius::CircleCollider2D::CheckCollision(CircleCollider2D* circle)
{
	return Collision(this->m_Circle2D, circle->m_Circle2D);
}

bool Rius::CircleCollider2D::CheckCollision(BoxCollider2D* collider)
{
	return Collision(this->m_Circle2D, collider->GetRectangle());
}

bool Rius::CircleCollider2D::CheckCollision(BoxCollider3D* collider)
{
	std::cout << "Error => 3D collider tries to collide with a 2D collider\n";
	return false;
}

bool Rius::CircleCollider2D::CheckCollision(CircleCollider3D* circle)
{
	std::cout << "Error => 3D collider tries to collide with a 2D collider\n";
	return false;
}

Rius::BaseComponent* Rius::CircleCollider2D::Clone()
{
	return new CircleCollider2D{ *this };
}

void Rius::CircleCollider2D::SetComponent(BaseComponent* comp)
{
	CircleCollider2D* component = static_cast<CircleCollider2D*>(comp);
	this->m_CollidersInCollision = component->m_CollidersInCollision;
	this->m_pGameObject = component->m_pGameObject;
	this->m_PreviousPos = component->m_PreviousPos;
	this->m_Trigger = component->m_Trigger;
	this->m_Circle2D = component->m_Circle2D;
}

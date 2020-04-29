#include "MiniginPCH.h"
#include "CircleCollider3D.h"
#include "BoxCollider3D.h"
#include "ExtraMathFiles.h"

Rius::CircleCollider3D::CircleCollider3D(Circle3D circle, bool IsTrigger)
	:Collider(IsTrigger)
{
}

Rius::CircleCollider3D::~CircleCollider3D()
{
}

Rius::CircleCollider3D::CircleCollider3D(const CircleCollider3D& other)
	: Collider(other.m_Trigger)
{
	this->m_CollidersInCollision = other.m_CollidersInCollision;
	this->m_pGameObject = other.m_pGameObject;
	this->m_PreviousPos = other.m_PreviousPos;
	this->m_Trigger = other.m_Trigger;
	this->m_Circle3D = other.m_Circle3D;
}

Rius::BaseComponent* Rius::CircleCollider3D::Clone()
{
	return new CircleCollider3D{ *this };
}

void Rius::CircleCollider3D::SetComponent(BaseComponent* comp)
{
	CircleCollider3D* component = static_cast<CircleCollider3D*>(comp);
	this->m_CollidersInCollision = component->m_CollidersInCollision;
	this->m_pGameObject = component->m_pGameObject;
	this->m_PreviousPos = component->m_PreviousPos;
	this->m_Trigger = component->m_Trigger;
	this->m_Circle3D = component->m_Circle3D;
}

void Rius::CircleCollider3D::Initialize()
{
}

void Rius::CircleCollider3D::Update()
{
	//TODO Can try to change it to the collider.h file but problem with checkCollisiion
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

void Rius::CircleCollider3D::Render() const
{
}

bool Rius::CircleCollider3D::CheckCollision(CircleCollider2D* circle)
{
	//TODO Change all the errors with the gmui
	std::cout << "Error => 3D collider tries to collide with a 2D collider\n";
	return false;
}

bool Rius::CircleCollider3D::CheckCollision(BoxCollider2D* collider)
{
	std::cout << "Error => 3D collider tries to collide with a 2D collider\n";
	return false;
}

bool Rius::CircleCollider3D::CheckCollision(CircleCollider3D* circle)
{
	return Collision(this->m_Circle3D, circle->m_Circle3D);
}

bool Rius::CircleCollider3D::CheckCollision(BoxCollider3D* collider)
{
	return Collision(this->m_Circle3D, collider->GetRectangle());
}

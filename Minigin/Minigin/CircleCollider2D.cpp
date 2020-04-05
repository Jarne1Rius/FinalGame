#include "MiniginPCH.h"
#include "CircleCollider2D.h"
#include  "ExtraMathFiles.h"
#include "BoxCollider2D.h"
Rius::CircleCollider2D::~CircleCollider2D()
{
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
			//exit collider
			if (m_Trigger) OnTriggerStay(collider);
			else OnCollisionStay(collider);
		}
		else if (newHit != hit && hit == false)
		{
			//exit collider
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

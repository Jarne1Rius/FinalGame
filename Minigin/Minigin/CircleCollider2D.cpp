#include "MiniginPCH.h"
#include "CircleCollider2D.h"
#include  "ExtraMathFiles.h"
#include "BoxCollider2D.h"

#include "Logger.h"

Rius::CircleCollider2D::CircleCollider2D(Circle2D circle, bool isTrigger, CollisionGroup collisionGroup)
	:Collider(isTrigger, collisionGroup), m_Circle2D(circle),m_StartPos(circle.pos,0)
{
}

Rius::CircleCollider2D::~CircleCollider2D()
{
}

Rius::CircleCollider2D::CircleCollider2D(const CircleCollider2D& other)
	: Collider(other.m_Trigger, other.m_CurrentCollisionGroup),m_StartPos(other.m_StartPos)
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

void Rius::CircleCollider2D::Update(float )
{
	if (!m_Static && m_CurrentCollisionGroup != Group3)
	{
		m_Circle2D.pos = m_pGameObject->GetTransform().GetPosition() + m_StartPos;
	}
	bool anyHit{ false };
	if (this->m_Static) return;
	for (Collider* collider : m_AllColliders)
	{
		if (collider == this || m_IgnoreGroups[collider->GetCurrentCollisionGroup()]) continue;
		bool newHit = collider->CheckCollision(this);
		if (newHit)
		{
			anyHit = true;
			if (m_Trigger || collider->IsTrigger())
			{
				m_pGameObject->OnTriggerEnter(collider);
				collider->GetGameObject()->OnTriggerEnter(this);
			}
			else
			{
				m_pGameObject->OnCollisionEnter(collider);
				collider->GetGameObject()->OnCollisionEnter(this);
			}
		}

	}

	m_PrevHit = anyHit;
}

void Rius::CircleCollider2D::Render() const
{
}

glm::vec2 Rius::CircleCollider2D::GetCenter()
{
	return m_Circle2D.pos;
}

bool Rius::CircleCollider2D::CheckCollision(CircleCollider2D* circle)
{
	return Collision(this->m_Circle2D, circle->m_Circle2D);
}

bool Rius::CircleCollider2D::CheckCollision(BoxCollider2D* collider)
{
	return Collision(this->m_Circle2D, collider->GetRectangle());
}

bool Rius::CircleCollider2D::CheckCollision(BoxCollider3D* )
{
	Logger::LogError("3D collider tries to collide with a 2D collider");
	return false;
}

bool Rius::CircleCollider2D::CheckCollision(CircleCollider3D* )
{
	Logger::LogError("3D collider tries to collide with a 2D collider");
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

#include "MiniginPCH.h"
#include "CircleCollider3D.h"
#include "BoxCollider3D.h"
#include "ExtraMathFiles.h"
#include "Logger.h"

Rius::CircleCollider3D::CircleCollider3D(Circle3D circle, bool IsTrigger, CollisionGroup collisionGroup)
	:Collider(IsTrigger, collisionGroup),m_StartPos(circle.pos),m_Circle3D(circle)
{
}

Rius::CircleCollider3D::~CircleCollider3D()
{
}

Rius::CircleCollider3D::CircleCollider3D(const CircleCollider3D& other)
	: Collider(other.m_Trigger, other.m_CurrentCollisionGroup)
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

void Rius::CircleCollider3D::Update(float )
{
	if (!m_Static && m_CurrentCollisionGroup != Group3)
	{
		m_Circle3D.pos = m_pGameObject->GetTransform().GetPosition() + m_StartPos;
		m_Circle3D.pos.y *= -1;
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

void Rius::CircleCollider3D::Render() const
{
}

glm::vec2 Rius::CircleCollider3D::GetCenter()
{
	return m_Circle3D.pos;
}

bool Rius::CircleCollider3D::CheckCollision(CircleCollider2D* )
{
	Logger::LogError("3D collider tries to collide with a 2D collider");
	return false;
}

bool Rius::CircleCollider3D::CheckCollision(BoxCollider2D* )
{
	Logger::LogError("3D collider tries to collide with a 2D collider");
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

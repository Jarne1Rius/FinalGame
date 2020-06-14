#include "MiniginPCH.h"
#include "BoxCollider3D.h"
#include "CircleCollider3D.h"
#include "ExtraMathFiles.h"
#include "Logger.h"

Rius::BoxCollider3D::BoxCollider3D(Rectangle3D rectangle,const glm::vec3& center, bool isTrigger, CollisionGroup collisionGroup )
	:Collider(isTrigger, collisionGroup), m_Center(-rectangle.width * center.x, rectangle.height* center.y, rectangle.depth * center.z),m_StartRectangle(center),m_Rectangle(rectangle)
{
}

Rius::BoxCollider3D::~BoxCollider3D()
{
}

Rius::BoxCollider3D::BoxCollider3D(const BoxCollider3D& other)
	: Collider(other.m_Trigger, other.m_CurrentCollisionGroup), m_Rectangle(other.m_Rectangle),m_StartRectangle(other.m_StartRectangle),m_Center(other.m_Center)
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

void Rius::BoxCollider3D::Update(float )
{
	if (!m_Static && m_CurrentCollisionGroup != Group3)
	{
		m_Rectangle.pos = m_pGameObject->GetTransform().GetPosition() + m_Center + m_StartRectangle;
		m_Rectangle.pos.y *= -1;
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

void Rius::BoxCollider3D::Render() const
{
}

glm::vec2 Rius::BoxCollider3D::GetCenter()
{
	return m_Rectangle.pos;
}

bool Rius::BoxCollider3D::CheckCollision(CircleCollider2D* )
{
	Logger::LogError("3D collider tries to collide with a 2D collider");
	return false;
}

bool Rius::BoxCollider3D::CheckCollision(BoxCollider2D* )
{
	Logger::LogError("3D collider tries to collide with a 2D collider");
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

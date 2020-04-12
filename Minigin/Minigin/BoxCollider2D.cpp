#include "MiniginPCH.h"
#include "BoxCollider2D.h"
#include "Extra.h"
#include "CircleCollider2D.h"
#include "GameObject.h"
#include "ExtraMathFiles.h"
Rius::BoxCollider2D::BoxCollider2D(Rectangle2D rectangle, bool isTrigger)
	:Collider(isTrigger),m_Rectangle(0,0,1,1)
{
	
}

Rius::BoxCollider2D::~BoxCollider2D()
{
}

void Rius::BoxCollider2D::Initialize()
{
}

void Rius::BoxCollider2D::Update()
{
	bool anyHit{false};
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
		if (newHit) anyHit = newHit;
		it->second = newHit;
	}
	if (anyHit) GetGameObject()->GetTransform().SetPosition(m_PreviousPos);
	m_PreviousPos = GetGameObject()->GetTransform().GetPosition();
}

void Rius::BoxCollider2D::Render() const
{
}

bool Rius::BoxCollider2D::CheckCollision(CircleCollider2D* circle)
{
	return Collision(this->m_Rectangle, circle->GetCircle2D());
}

bool Rius::BoxCollider2D::CheckCollision(BoxCollider2D* collider)
{
	return Collision(this->m_Rectangle, collider->m_Rectangle);
}

#include "MiniginPCH.h"
#include "Collider.h"
#include "ExtraMathFiles.h"

Rius::Collider::Collider(bool isTrigger)
	:m_Trigger(isTrigger)
{
	//m_AllColliders.push_back(this);
}

Rius::Collider::~Collider()
{
}

void Rius::Collider::DeleteCollider(Collider* collider)
{
	m_CollidersInCollision.erase(collider);
	
}

void Rius::Collider::AddCollider(Collider* collider)
{
	m_CollidersInCollision.insert(std::pair<Collider*, bool>(collider, false));
}

void Rius::Collider::SetCollisions()
{
	for (Collider* collider : m_AllColliders)
	{
		m_CollidersInCollision.insert(std::pair<Collider*, bool>(collider, false));
	}
}

void Rius::Collider::ChangeTrigger(bool isTrigger)
{
	m_Trigger = isTrigger;
}

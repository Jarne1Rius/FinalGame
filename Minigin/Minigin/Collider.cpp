#include "MiniginPCH.h"
#include "Collider.h"
#include "ExtraMathFiles.h"
#include "Minigin.h"

std::vector<Rius::Collider*> Rius::Collider::m_AllColliders = std::vector<Rius::Collider*>{};
Rius::Collider::Collider(bool isTrigger, CollisionGroup collisionGroup)
	:m_Trigger(isTrigger), m_CurrentCollisionGroup(collisionGroup)
{
	AddColliderToAllColliders(this);
}

Rius::Collider::~Collider()
{
	RemoveColliderOfAllColliders(this);
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
		collider->AddCollider(this);
	}
}

void Rius::Collider::ChangeTrigger(bool isTrigger)
{
	m_Trigger = isTrigger;
	Minigin::m_UndoSystem.AddAction(this);
}

void Rius::Collider::SetIgnore(bool ignore)
{
	m_IgnoreCollisionGroup = ignore;
}

void Rius::Collider::SetIgnoreGroups(CollisionGroup group, bool ignore)
{
	m_IgnoreGroups[group] = ignore;
}

void Rius::Collider::SetIgnoreGroups(bool ignore[Group3 + 1])
{
	for (int i = 0; i < Group3; ++i)
	{
		m_IgnoreGroups[i] = ignore[i];
	}
}

void Rius::Collider::SetCollisionGroup(CollisionGroup group)
{
	m_CurrentCollisionGroup = group;
}


void Rius::Collider::AddColliderToAllColliders(Collider* collider)
{
	m_AllColliders.push_back(collider);
	collider->SetCollisions();

}

void Rius::Collider::RemoveColliderOfAllColliders(Collider* collider)
{
	m_AllColliders.erase(std::find(m_AllColliders.begin(), m_AllColliders.end(), collider));
}
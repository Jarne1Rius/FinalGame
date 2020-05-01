#include "MiniginPCH.h"
#include "Collider.h"
#include "ExtraMathFiles.h"
#include "Minigin.h"

std::vector<Rius::Collider*> Rius::Collider::m_AllColliders = std::vector<Rius::Collider*>{};
Rius::Collider::Collider(bool isTrigger)
	:m_Trigger(isTrigger)
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

void Rius::Collider::AddColliderToAllColliders(Collider* collider)
{
	m_AllColliders.push_back(collider);
	collider->SetCollisions();

}

void Rius::Collider::RemoveColliderOfAllColliders(Collider* collider)
{
	m_AllColliders.erase(std::find(m_AllColliders.begin(), m_AllColliders.end(), collider));
}
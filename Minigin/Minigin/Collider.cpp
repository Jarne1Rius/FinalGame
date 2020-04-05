#include "MiniginPCH.h"
#include "Collider.h"

Rius::Collider::Collider()
{
}

Rius::Collider::~Collider()
{
}

void Rius::Collider::DeleteCollider(Collider* collider)
{
	m_CollidersInCollision.insert(std::pair<Collider*, bool>(collider, false));
}

void Rius::Collider::AddCollider(Collider* collider)
{
	m_CollidersInCollision.erase(collider);
}

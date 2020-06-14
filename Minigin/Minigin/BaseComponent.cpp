#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "GameObject.h"
#include "RigidBodyComponent.h"
#include "Collider.h"
int Rius::BaseComponent::m_CurrentID = 0;
Rius::BaseComponent::BaseComponent()
	:m_pGameObject(nullptr), m_Id(m_CurrentID)
{
	m_CurrentID++;
}


void Rius::BaseComponent::SetComponent(BaseComponent* comp)
{
	*this = *comp;
}

Rius::BaseComponent* Rius::BaseComponent::Clone()
{
	return nullptr;
}

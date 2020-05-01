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

void Rius::BaseComponent::LateUpdate()
{
}

void Rius::BaseComponent::OnTriggerEnter(Collider* collider)
{
}

void Rius::BaseComponent::OnTriggerStay(Collider* collider)
{
}

void Rius::BaseComponent::OnCollisionEnter(Collider* collider)
{
	RigidBodyComponent* com = m_pGameObject->GetRigidBodyComponent();

	if (com)
	{
		

		com->Bounce(1.f);
	}
}

void Rius::BaseComponent::OnTriggerExit(Collider* collider)
{
}

void Rius::BaseComponent::OnCollisionStay(Collider* collider)
{
}

void Rius::BaseComponent::OnCollisionExit(Collider* collider)
{
}

Rius::BaseComponent* Rius::BaseComponent::Clone()
{
	return nullptr;
}

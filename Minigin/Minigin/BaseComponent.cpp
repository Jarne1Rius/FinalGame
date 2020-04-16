#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "GameObject.h"
#include "RigidBodyComponent.h"
Rius::BaseComponent::BaseComponent()
	:m_pGameObject(nullptr)
{
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
	RigidBodyComponent* com = m_pGameObject->GetComponent<RigidBodyComponent>();
	if(com)
	{
		com->Bounce(0.5f);
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

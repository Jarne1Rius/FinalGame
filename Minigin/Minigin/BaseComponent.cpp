#include "MiniginPCH.h"
#include "BaseComponent.h"

Rius::BaseComponent::BaseComponent()
	:m_pGameObject(nullptr)
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

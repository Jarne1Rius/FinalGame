#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include  "Texture2D.h"
#include "RigidBodyComponent.h"
#include "PlayerComponent.h"

int Rius::GameObject::m_CurrentID = 0;
Rius::GameObject::GameObject()
	:m_pComponents(), m_pChildren(), m_pParentObject(), m_Tag(), m_Static(), m_Transform(), m_pParentScene(), m_pRigidBodyComponent(nullptr)
	, m_Id(), m_Active(true), m_pPlayerComponent(), m_PreviousPos()
{
	m_Id = m_CurrentID;
	m_CurrentID++;
}

Rius::GameObject::~GameObject()
{
	for (int i{}; i < int(m_pComponents.size()) ;i++)
	{
		delete m_pComponents[i];
	}
	delete m_pParentObject;
	for (int i{}; i < int(m_pChildren.size()); i++)
		delete m_pChildren[i];
}

void Rius::GameObject::AddComponent(BaseComponent* component)
{
	component->m_pGameObject = this;
	m_pComponents.push_back(component);
}

void Rius::GameObject::AddComponent(RigidBodyComponent* rigid)
{
	rigid->m_pGameObject = this;
	m_pRigidBodyComponent = rigid;
	m_pComponents.push_back(rigid);
}

void Rius::GameObject::AddComponent(PlayerComponent* playerComponent)
{
	playerComponent->m_pGameObject = this;
	m_pPlayerComponent = playerComponent;
	m_pComponents.push_back(playerComponent);
}

void Rius::GameObject::OnTriggerEnter(Collider* other)
{
	for (BaseComponent* baseComponent : m_pComponents)
	{
		baseComponent->OnTriggerEnter(other);
	}
}

void Rius::GameObject::OnCollisionEnter(Collider* other)
{
	for (BaseComponent* baseComponent : m_pComponents)
	{
		baseComponent->OnCollisionEnter(other);
	}
}

Rius::BaseComponent* Rius::GameObject::GetComponentById(int id)
{
	for (BaseComponent* comp : m_pComponents)
		if (comp->GetId() == id) return comp;
	return nullptr;
}

void Rius::GameObject::Update(float deltaT)
{
	if (!m_Active) return;
	for (BaseComponent* comp : m_pComponents)
	{
		if(comp != m_pRigidBodyComponent)
			comp->Update(deltaT);
	}
	if (m_pRigidBodyComponent != nullptr)
		m_pRigidBodyComponent->Update(deltaT);
}

void Rius::GameObject::LateUpdate()
{
	if (!m_Active) return;
	for (BaseComponent* comp : m_pComponents)
		comp->LateUpdate();
}

void Rius::GameObject::Render() const
{
	if (!m_Active) return;
	for (BaseComponent* comp : m_pComponents)
		comp->Render();
	//const auto pos = m_Transform.GetPosition();
	//Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}

void Rius::GameObject::Initialize()
{
	for (BaseComponent* comp : m_pComponents)
		comp->Initialize();
}

Rius::GameObject* Rius::GameObject::Clone()
{
	return this;
}


void Rius::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

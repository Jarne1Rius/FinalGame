#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include  "Texture2D.h"

int Rius::GameObject::m_CurrentID = 0;
Rius::GameObject::GameObject()
	:m_pComponents(), m_pChildren(), m_pParentObject(), m_Tag(), m_Static(), m_Transform(), m_pParentScene()
{
	m_Id = m_CurrentID;
	m_CurrentID++;
}

Rius::GameObject::~GameObject()
{
	for (int i{}; i < int(m_pComponents.size()); i++)
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

Rius::BaseComponent* Rius::GameObject::GetComponentById(int id)
{
	for (BaseComponent* comp : m_pComponents)
		if (comp->GetId() == id) return comp;
	return nullptr;
}

void Rius::GameObject::Update()
{
	for (BaseComponent* comp : m_pComponents)
		comp->Update();
}

void Rius::GameObject::LateUpdate()
{
	for (BaseComponent* comp : m_pComponents)
		comp->LateUpdate();
}

void Rius::GameObject::Render() const
{
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


void Rius::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

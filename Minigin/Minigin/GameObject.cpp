#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include  "Texture2D.h"

Rius::GameObject::GameObject()
	:m_pComponents(),m_pChildren(),m_pParentObject(),m_Tag(),m_Static(),m_Transform(),m_pParentScene()
{
}

Rius::GameObject::~GameObject()
{
	for (int i {}; i < int(m_pComponents.size()); i++)
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

void Rius::GameObject::Update()
{
	for (BaseComponent* comp : m_pComponents)
		comp->Update();
}

void Rius::GameObject::Render() const
{
	for (BaseComponent* comp : m_pComponents)
		comp->Render();
	//const auto pos = m_Transform.GetPosition();
	//Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}


void Rius::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

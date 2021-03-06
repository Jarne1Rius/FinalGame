#include "MiniginPCH.h"
#include "HealthComponent.h"
#include "GameObject.h"
#include "MaterialManager.h"
#include "Minigin.h"
#include "TextureMaterial.h"

Rius::HealthComponent::HealthComponent(int health, bool leftSide)
	:m_LeftSide(leftSide), m_Health(health), m_OriginalHealth(health),m_Sprites{},m_pMat()
{
	m_pMat = new TextureMaterial{ "Resources/Enemy/Enemy.png","Health" + std::to_string(MaterialManager::m_ID),"Health" + std::to_string(MaterialManager::m_ID),true };
	MaterialManager::AddMaterial(m_pMat);
}

Rius::HealthComponent::~HealthComponent()
{
	for (int i = 0; i < m_OriginalHealth; ++i)
	{
		delete m_Sprites[i];
	}
}

void Rius::HealthComponent::Initialize()
{
	float scale{ 20 };
	glm::vec2 startPos = (m_LeftSide) ? glm::vec2{ 5,5 } : glm::vec2{ Minigin::m_Width - scale - 5,5 };

	for (int i = 0; i < m_Health; ++i)
	{
		SpriteRenderer* sprite = new SpriteRenderer{ m_pGameObject->GetTransform().GetPosition(),m_pMat,{startPos,scale,scale},false,ConvertToUVCoordinates(((m_LeftSide) ? Rectangle2D{84,84,8,6} : Rectangle2D{95,84,8,6}),m_pMat->GetTexture2D()) };
		m_Sprites[i] = sprite;


		startPos.x += (m_LeftSide) ? scale : -scale;
	}
}

void Rius::HealthComponent::Update(float )
{
	for (int i = 0; i < m_Health; ++i)
	{
		m_Sprites[i]->LateUpdate(m_pGameObject->GetTransform().GetPosition());
	}
}

void Rius::HealthComponent::LateUpdate()
{
}

void Rius::HealthComponent::Render() const
{
	for (int i = 0; i < m_Health; ++i)
	{
		m_Sprites[i]->Render();
	}
}

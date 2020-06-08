#include "MiniginPCH.h"
#include "HealthComponent.h"
#include "GameObject.h"
#include "Minigin.h"
#include "TextureMaterial.h"

Rius::HealthComponent::HealthComponent(int health, bool leftSide)
	:m_LeftSide(leftSide), m_Health(health),m_OriginalHealth(health)
{
	m_pMat = new TextureMaterial{ "../Data/SpriteSheet.png","Health","Health",true };
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
	float scale{ 30 };
	glm::vec2 startPos =(m_LeftSide)? glm::vec2{ 0,0 } : glm::vec2{Minigin::m_Width - scale,0};

	for (int i = 0; i < m_Health; ++i)
	{
		SpriteRenderer* sprite = new SpriteRenderer{ m_pGameObject->GetTransform().GetPosition(),m_pMat,{startPos,scale,scale},true,ConvertToUVCoordinatess(((m_LeftSide) ? Rectangle2D{601,830,10,10} : Rectangle2D{613,830,10,10}),m_pMat->GetTexture2D()) };
		m_Sprites[i] = sprite;

		
		startPos.x += (m_LeftSide)? scale: -scale;
	}
}

void Rius::HealthComponent::Update()
{
	for (int i = 0; i < m_Health; ++i)
	{
		m_Sprites[i]->Update();
	}
}

void Rius::HealthComponent::Render() const
{
	for (int i = 0; i < m_Health; ++i)
	{
		m_Sprites[i]->Render();
	}
}

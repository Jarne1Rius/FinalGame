#include "MiniginPCH.h"
#include "WallComponent.h"
#include "TextureMaterial.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
Rius::WallComponent::WallComponent( glm::vec2 texCoordinateOffset, TextureMaterial* material, const Rectangle2D& startPos, float width, float height)
	:m_pSprite(), m_PMat(material), m_Offset(texCoordinateOffset), m_StartPos(startPos), m_Width(width), m_Height(height)
{
}

Rius::WallComponent::~WallComponent()
{
	delete m_pSprite;
}

void Rius::WallComponent::Initialize()
{
	m_pSprite = new SpriteRenderer{ m_pGameObject->GetTransform().GetPosition(),m_PMat,m_StartPos,true,{m_Offset.x,m_Offset.y,float(m_StartPos.width / m_Width), m_StartPos.height / m_Height} };
}

void Rius::WallComponent::Render() const
{
	m_pSprite->Render();
}

void Rius::WallComponent::Update(float deltaT)
{
//	m_pSprite->Update();
}

void Rius::WallComponent::LateUpdate()
{
	m_pSprite->LateUpdate(m_pGameObject->GetTransform().GetPosition());
}

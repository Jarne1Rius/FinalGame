#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "TextureMaterial.h"
#include "SpriteRenderer.h"

Rius::SpriteComponent::SpriteComponent(TextureMaterial* textureBullet, const Rectangle2D& texCoordSizeOfTexture, float scale)
	:m_Sprite(), m_PMat(textureBullet),m_TexCoord(texCoordSizeOfTexture),m_Scale(scale)
{
	
}

Rius::SpriteComponent::~SpriteComponent()
{
	delete m_Sprite;
}

Rius::SpriteComponent::SpriteComponent(const SpriteComponent& other)
	:m_TexCoord(other.m_TexCoord),m_Sprite(other.m_Sprite),m_PMat(other.m_PMat)
{
}

void Rius::SpriteComponent::Initialize()
{
	m_Sprite = new SpriteRenderer{ m_pGameObject->GetTransform().GetPosition(),m_PMat,{0,0,m_Scale,m_Scale},false,ConvertToUVCoordinates(m_TexCoord, m_PMat->GetTexture2D())};
}

void Rius::SpriteComponent::Update(float deltaT)
{
	m_Sprite->LateUpdate(m_pGameObject->GetTransform().GetPosition());
}

void Rius::SpriteComponent::Render() const
{
	m_Sprite->Render();
}

Rius::BaseComponent* Rius::SpriteComponent::Clone()
{
	return new SpriteComponent{ *this };
}
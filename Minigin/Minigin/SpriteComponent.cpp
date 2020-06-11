#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "TextureMaterial.h"
#include "SpriteRenderer.h"

Rius::SpriteComponent::SpriteComponent(TextureMaterial* textureBullet, const Rectangle2D& texCoordSizeOfTexture)
	:m_Sprite(), m_PMat(textureBullet),m_TexCoord(texCoordSizeOfTexture)
{
	
}

Rius::SpriteComponent::~SpriteComponent()
{
}

void Rius::SpriteComponent::Initialize()
{
	m_Sprite = new SpriteRenderer{ m_pGameObject->GetTransform().GetPosition(),m_PMat,{0,0,1,1},false,ConvertToUVCoordinates(m_TexCoord, m_PMat->GetTexture2D())};
}

void Rius::SpriteComponent::Update()
{
}

void Rius::SpriteComponent::Render() const
{
	m_Sprite->Render();
}

Rius::SpriteComponent* Rius::SpriteComponent::Cloning()
{
	return new SpriteComponent{this->m_PMat,m_TexCoord};
}
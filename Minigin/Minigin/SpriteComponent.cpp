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
	delete m_Sprite;
}

void Rius::SpriteComponent::Initialize()
{
	m_Sprite = new SpriteRenderer{ m_pGameObject->GetTransform().GetPosition(),m_PMat,{0,0,100,100},false,{0,0,1,1} };//ConvertToUVCoordinates(m_TexCoord, m_PMat->GetTexture2D())};
}

void Rius::SpriteComponent::Update(float deltaT)
{
	m_Sprite->LateUpdate(m_pGameObject->GetTransform().GetPosition());
}

void Rius::SpriteComponent::Render() const
{
	m_Sprite->Render();
}

Rius::SpriteComponent* Rius::SpriteComponent::Cloning()
{
	return new SpriteComponent{this->m_PMat,m_TexCoord};
}

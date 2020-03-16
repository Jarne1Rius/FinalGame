#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"

Rius::TextureComponent::TextureComponent(const std::string& fileName,const glm::vec2& position)
	:BaseComponent(), m_Transform({ position.x, position.y, 0 })
{
	SetTexture(fileName);
}

Rius::TextureComponent::~TextureComponent()
{
	delete m_pTexture;
}

void Rius::TextureComponent::Update()
{
}

void Rius::TextureComponent::Initialize()
{
}

void Rius::TextureComponent::Render() const
{
	const auto pos = m_Transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
}

void Rius::TextureComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void Rius::TextureComponent::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

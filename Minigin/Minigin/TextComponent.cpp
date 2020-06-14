#include "MiniginPCH.h"
#include "TextComponent.h"

#include "MaterialManager.h"
#include "TextMaterial.h"
Rius::TextComponent::TextComponent(const std::string& text, const glm::vec3& color, const glm::vec2& offset, float size)
{
	m_pMat = new TextMaterial{ "Textf" + std::to_string(MaterialManager::m_ID),color };
	MaterialManager::AddMaterial(m_pMat);
	m_TextRenderer = new TextRenderer{ offset,m_pMat,text,"Resources/Lingua.otf",24,size };
}

Rius::TextComponent::~TextComponent()
{
	delete m_TextRenderer;
}

void Rius::TextComponent::Initialize()
{
}

void Rius::TextComponent::Update(float )
{
}

void Rius::TextComponent::Render() const
{
	m_TextRenderer->Render();
}

void Rius::TextComponent::ChangeText(const std::string& text)
{
	m_TextRenderer->ChangeText(text);
}

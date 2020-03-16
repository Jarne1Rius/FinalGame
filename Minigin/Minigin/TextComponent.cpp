#include "MiniginPCH.h"
#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include  "GameObject.h"
#include <SDL.h>
#include <SDL_ttf.h>

Rius::TextComponent::TextComponent(const std::string& text,Font* font, const glm::vec2& position)
	:BaseComponent()
	, m_NeedsUpdate(true)
	, m_Text(text)
	, m_pFont(font)
	, m_Transform({position.x, position.y,0})
	, m_Texture(nullptr)
{
}

Rius::TextComponent::~TextComponent()
{
	delete m_pFont;
}

void Rius::TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_Texture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void Rius::TextComponent::Initialize()
{
}

void Rius::TextComponent::Render() const
{
	if (m_Texture != nullptr)
	{
		const auto pos = m_Transform.GetPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

void Rius::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void Rius::TextComponent::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

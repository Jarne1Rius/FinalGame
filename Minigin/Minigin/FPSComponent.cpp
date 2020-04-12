#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include  "GameObject.h"
#include "Time.h"
#include <SDL.h>
#include <SDL_ttf.h>

Rius::FPSComponent::FPSComponent(Font* font, const glm::vec2& position)
	:BaseComponent()
	, m_pFont(font)
	, m_Transform({ position.x, position.y,0 })
	, m_Texture(nullptr)
	, m_Frames()
{
}

Rius::FPSComponent::~FPSComponent()
{
	delete m_Texture;
	delete m_pFont;
}

void Rius::FPSComponent::Update()
{
	if (m_Frames != Rius::Time::GetInstance().GetFrames())
	{
		m_Frames = Rius::Time::GetInstance().GetFrames();
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), (std::to_string(m_Frames) + " FPS").c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		//Texture2D* texture = new Texture2D(SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf));
		//if (texture == nullptr)
		//{
		//	throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		//}
	//	SDL_FreeSurface(surf);
		//delete m_Texture;
		//m_Texture = (texture);
	}
}

void Rius::FPSComponent::Initialize()
{

}

void Rius::FPSComponent::Render() const
{
	if (m_Texture != nullptr)
	{
		const auto pos = m_Transform.GetPosition();
		//Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

void Rius::FPSComponent::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

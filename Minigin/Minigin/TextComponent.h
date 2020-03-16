#pragma once
#include "BaseComponent.h"
#include <string>
#include <memory>
#include "Transform.h"
#include "glm/glm.hpp"
namespace Rius
{
	class Font;
	class Texture2D;
	class Transform;
	class TextComponent :
		public BaseComponent
	{
	public:
		TextComponent(const std::string& text, Font* font, const glm::vec2& position = {0,0});
		virtual ~TextComponent() ;
		void Update() override;
		void Initialize() override;
		void Render() const override;
		void SetText(const std::string& text);
		void SetPosition(float x, float y);
		Transform GetTransform() const { return  m_Transform; }

	private:
		bool m_NeedsUpdate;
		Transform m_Transform;
		std::string m_Text;
		Font* m_pFont;
		std::shared_ptr<Texture2D> m_Texture;
	};
}
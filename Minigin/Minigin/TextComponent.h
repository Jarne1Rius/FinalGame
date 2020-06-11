#pragma once
#include "BaseComponent.h"
#include "TextRenderer.h"

namespace Rius
{
	class TextComponent final :
		public BaseComponent
	{
	public:
		TextComponent(const std::string& text,const glm::vec3& color, const glm::vec2& offset, float size = 1);
		~TextComponent();
		void Initialize() override;
		void Update() override;
		void Render() const override;

		void ChangeText(const std::string& text);
	private:
		TextRenderer* m_TextRenderer;
		TextMaterial* m_pMat;
	};
}

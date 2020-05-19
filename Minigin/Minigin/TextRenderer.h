#pragma once

#include "BaseComponent.h"
#include "Extra.h"
#include <string>

#include "Shader.h"
#include <map>

namespace Rius
{
	struct Character {
		unsigned int TextureID;
		glm::ivec2   Size;     
		glm::ivec2   Bearing;  
		unsigned int Advance;  
	};
	class TextRenderer : public BaseComponent
	{
	public:
		TextRenderer(std::string text);
		~TextRenderer();
		void SetComponent(BaseComponent* comp) override;
		void Initialize() override;
		BaseComponent* Clone() override;
		void Update() override;
		void Render() const override;
		void ChangeText(std::string& text) { m_Text = text; }
		
	private:
		void Load(std::string font, int fontSize);
		Shader* m_TextShader;
		std::map<char, Character> Characters;
		unsigned int m_VBO, m_VAO;
		std::string m_Text;
		Rectangle2D m_Src;
	};

}


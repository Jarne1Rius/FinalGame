#pragma once

#include "BaseComponent.h"
#include "Extra.h"
#include <string>

#include <map>


namespace Rius
{
	class TextMaterial;

	struct Character {
		unsigned int TextureID;
		glm::ivec2   Size = {0,0};     
		glm::ivec2   Bearing = {0,0};  
		unsigned int Advance;  
	};
	class TextRenderer final
	{
	public:
		TextRenderer(const glm::vec2& localPos,TextMaterial* material, std::string text, std::string font = "Resources/Lingua.otf", int size = 24, float scale = 1);
		~TextRenderer();
		void Render() const ;
		void RenderText(const glm::vec2& pos, std::string text, float scale, glm::vec3 color = glm::vec3{-1,0,0}) const;
		void ChangeText(const std::string& text) { m_Text = text; }
		void SetPos(const glm::vec2& pos);
		
	private:
		void Initialize();
		void Load(std::string font, int fontSize);
		TextMaterial* m_TextMaterial;
		std::map<char, Character> Characters;
		unsigned int m_VBO, m_VAO;
		std::string m_Text;
		float m_Scale;
		glm::vec2 m_Pos;
	};

}


#include "MiniginPCH.h"
#include "TextRenderer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H


#include "ResourceManager.h"

Rius::TextRenderer::TextRenderer(std::string text)
	:m_VBO(),m_VAO(),m_Src(5,5,1,1),m_TextShader(),m_Text(text)
{
	Load("Resources/Lingua.otf", 24);
	m_TextShader = ResourceManager::LoadShader("Shader/Text.vs", "Shader/Text.fs", "Text");
	m_TextShader->SetMat4("projection", glm::ortho(0.0f, static_cast<float>(1280), static_cast<float>(720),0.f));
	m_TextShader->Use();
	this->m_TextShader->SetInt("text", 0);
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Rius::TextRenderer::~TextRenderer()
{
	Characters.clear();
	//delete m_TextShader;
}

void Rius::TextRenderer::SetComponent(BaseComponent* comp)
{
}

void Rius::TextRenderer::Initialize()
{
}

Rius::BaseComponent* Rius::TextRenderer::Clone()
{
	return nullptr;
}

void Rius::TextRenderer::Update()
{
}
void Rius::TextRenderer::Render() const
{
	// activate corresponding render state	
	m_TextShader->Use();
	m_TextShader->SetVec3("textColor", {1,1,1});
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(m_VAO);
	float x, y;
	x = m_Src.pos.x;
	y = m_Src.pos.y;
	// iterate through all characters
	std::string::const_iterator c;
	for (c = m_Text.begin(); c != m_Text.end(); c++)
	{
		Character ch = Characters.at(*c);

		float xpos = x + ch.Bearing.x * 1;
		float ypos = y + (this->Characters.at('H').Bearing.y - ch.Bearing.y) * 1;

		float w = ch.Size.x * 1.f;
		float h = ch.Size.y * 1.f;
		// update VBO for each character
		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 0.0f },

			{ xpos,     ypos + h,   0.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 0.0f }
		};
		// render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// now advance cursors for next glyph
		x += (ch.Advance >> 6) * 1; // bitshift by 6 to get value in pixels (1/64th times 2^6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Rius::TextRenderer::Load(std::string font, int fontSize)
{
	this->Characters.clear();
	// then initialize and load the FreeType library
	FT_Library ft;
	if (FT_Init_FreeType(&ft)) // all functions return a value different than 0 whenever an error occurred
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	// load font as face
	FT_Face face;
	if (FT_New_Face(ft, font.c_str(), 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
	// set size to load glyphs as
	FT_Set_Pixel_Sizes(face, 0, fontSize);
	// disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	for (GLubyte c = 0; c < 128; c++) // lol see what I did there 
	{
		// load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// generate texture
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
		// set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// now store character for later use
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			unsigned int(face->glyph->advance.x)
		};
		Characters.insert(std::pair<char, Character>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	// destroy FreeType once we're finished
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

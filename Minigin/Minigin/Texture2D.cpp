#include "MiniginPCH.h"
#include "Texture2D.h"

#include <glad/glad.h>

#include "stb_image.h"

Rius::Texture2D::Texture2D()
	: m_Width(0), m_Height(0), m_InternalFormat(GL_RGB), m_ImageFormat(GL_RGB), m_WrapS(GL_REPEAT), m_WrapT(GL_REPEAT), m_FilterMin(GL_LINEAR), m_FilterMax(GL_LINEAR)
{
	glGenTextures(1, &this->m_Id);
}

void Rius::Texture2D::Generate(unsigned width, unsigned height, unsigned char* data)
{
    this->m_Width = width;
    this->m_Height = height;
    // Create Texture
    glBindTexture(GL_TEXTURE_2D, this->m_Id);
    stbi_set_flip_vertically_on_load(true);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_WrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_WrapT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_FilterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_FilterMax);
    glTexImage2D(GL_TEXTURE_2D, 0, this->m_InternalFormat, width, height, 0, this->m_ImageFormat, GL_UNSIGNED_BYTE, data);
    // Set Texture wrap and filter modes
    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Rius::Texture2D::Bind() const
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, this->m_Id);
}

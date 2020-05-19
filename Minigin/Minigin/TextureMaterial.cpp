#include "MiniginPCH.h"
#include "TextureMaterial.h"

#include "MaterialManager.h"

Rius::TextureMaterial::TextureMaterial(const std::string fileTexture, const std::string nameShader, const std::string nameTexture, bool transparent, glm::mat4& projectionMatrix)
	:m_Transparent(transparent), Material("Shader/SpriteTexture.vs", "Shader/SpriteTexture.fs", nameShader, projectionMatrix)
{
	m_pTexture = ResourceManager::LoadTexture(fileTexture.c_str(), m_Transparent, nameTexture);
	m_pShader->Use().SetBool("EnableTexture", true);
}


Rius::Texture2D* Rius::TextureMaterial::SetTexture(const std::string fileTexture, const std::string nameTexture, bool transparent)
{
	m_Transparent = transparent;
	ResourceManager::ClearTexture(m_pTexture);
	m_pTexture = ResourceManager::LoadTexture(fileTexture.c_str(), m_Transparent, nameTexture);
	return m_pTexture;
}


void Rius::TextureMaterial::UpdateVariables() const
{
	Material::UpdateVariables();
	if (m_pTexture != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		m_pTexture->Bind();
	}
}

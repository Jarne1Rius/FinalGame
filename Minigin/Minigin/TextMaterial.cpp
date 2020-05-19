#include "MiniginPCH.h"
#include "TextMaterial.h"

#include <glm/gtc/matrix_transform.hpp>


#include "Minigin.h"

Rius::TextMaterial::TextMaterial(const std::string nameShader, const glm::vec3& color)
	: Material{"Shader/Text.vs", "Shader/Text.fs", nameShader}, m_Color(color)
{
	glm::mat4x4 proj = glm::ortho(0.0f, static_cast<float>(Minigin::m_Width), static_cast<float>(Minigin::m_Height), 0.f);
	SetProjectionMatrix(proj);
	// ReSharper disable once CppExpressionWithoutSideEffects
	m_pShader->Use();
}

void Rius::TextMaterial::UpdateVariables() const
{
	Material::UpdateVariables();
	m_pShader->SetVec3("textColor", m_Color);
}

void Rius::TextMaterial::SetColor(glm::vec3 color)
{
	m_Color = color;
}

#include "MiniginPCH.h"
#include "Material.h"

Rius::Material::Material(std::string vertexShader, std::string fragmentShader, const std::string nameShader, glm::mat4& projectionMatrix )
	:m_ProjectionMatrix(projectionMatrix),m_ModelSpace()
{
	//LoadShader from file
	m_pShader = ResourceManager::LoadShader(vertexShader.c_str(), fragmentShader.c_str(), nameShader);
	//m_pShader->Use();
	m_pShader->SetMat4("projection", m_ProjectionMatrix);
}

Rius::Material::~Material()
{
}

void Rius::Material::SetProjectionMatrix(glm::mat4& projectionMatrix)
{
	m_ProjectionMatrix = projectionMatrix;
	m_pShader->SetMat4("projection", m_ProjectionMatrix);
}

Rius::Shader* Rius::Material::GetShader() const
{
	return m_pShader;
}

void Rius::Material::SetModelSpace(glm::mat4& modelSpace)
{
	m_ModelSpace = modelSpace;
}

void Rius::Material::UpdateVariables() const
{
	m_pShader->Use();

	m_pShader->SetMat4("model", m_ModelSpace);

}

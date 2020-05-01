#pragma once
#include "ResourceManager.h"
#include <glm/glm.hpp>
namespace Rius
{
	class Material
	{
	public:
		Material(const std::string nameShader, glm::mat4& projectionMatrix = ResourceManager::m_ProjectionMatrix) ;
		virtual ~Material();
		void SetProjectionMatrix(glm::mat4& projectionMatrix = ResourceManager::m_ProjectionMatrix);
		Shader* GetShader() const;
		void SetModelSpace(glm::mat4& modelSpace);
		virtual void UpdateVariables() const;
	private:
		Shader* m_pShader{};
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ModelSpace;
	};
}



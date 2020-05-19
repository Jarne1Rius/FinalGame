#pragma once
#include "ResourceManager.h"
#include <glm/glm.hpp>
namespace Rius
{
	class Material
	{
	public:
		Material(std::string vertexShader,std::string fragmentShader,const std::string nameShader, glm::mat4& projectionMatrix = ResourceManager::m_ProjectionMatrix) ;
		virtual ~Material();
		void SetProjectionMatrix(glm::mat4& projectionMatrix = ResourceManager::m_ProjectionMatrix);
		Shader* GetShader() const;
		void SetModelSpace(glm::mat4& modelSpace);
		virtual void UpdateVariables() const;
	protected:
		Shader* m_pShader;
		
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ModelSpace;
	};
}



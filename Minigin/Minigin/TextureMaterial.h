#pragma once
#include "Material.h"
namespace Rius
{
	class TextureMaterial : public Material
	{
	public:
		explicit TextureMaterial(const std::string fileTexture,const std::string nameShader,const std::string nameTexture,bool transparent = false, glm::mat4& projectionMatrix = ResourceManager::m_ProjectionMatrix);
		~TextureMaterial() = default;
		void UpdateVariables() const override;
		Texture2D* GetTexture2D() const { return m_pTexture; }
		//only by texture
		Texture2D* SetTexture(const std::string fileTexture,const std::string nameTexture, bool transparent = false);
	private:
		bool m_Transparent;
		Texture2D* m_pTexture;
	};
}


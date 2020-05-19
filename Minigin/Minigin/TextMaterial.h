#pragma once
#include "Material.h"

namespace Rius
{
	class TextMaterial : public Material
	{
	public:
		TextMaterial(const std::string nameShader, const glm::vec3& color);
		~TextMaterial() = default;
		void UpdateVariables() const override;
		void SetColor(glm::vec3 color);
	private:
		glm::vec3 m_Color;

	};
}

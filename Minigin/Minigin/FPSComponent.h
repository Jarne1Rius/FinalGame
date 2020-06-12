#pragma once
#include "BaseComponent.h"
#include <string>
#include <memory>
#include "Transform.h"
#include "glm/glm.hpp"
#include "TextRenderer.h"
namespace Rius
{
	class Font;
	class Transform;
	class FPSComponent : public BaseComponent
	{

	public:
		explicit FPSComponent(glm::vec3 color = { 0,0,0 }, const std::string& font = "Resources/Lingua.otf");
		virtual ~FPSComponent();
		void Update(float deltaT) override;
		void Initialize() override;
		void Render() const override;
		void SetComponent(BaseComponent* comp) override ;
		BaseComponent* Clone() override;
	private:
		TextRenderer* m_pTextRenderer;
		TextMaterial* m_pMat;
	};

}


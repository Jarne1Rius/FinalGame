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
	class FpsComponent final : public BaseComponent
	{

	public:
		explicit FpsComponent(glm::vec3 color = { 0,0,0 }, const std::string& font = "Resources/Lingua.otf");
		~FpsComponent();
		FpsComponent(const FpsComponent& other) = default;
		FpsComponent(FpsComponent&& other) noexcept = default;
		FpsComponent& operator= (const FpsComponent& other) = default;
		FpsComponent& operator= (FpsComponent&& other) = default;

		void Initialize() override;
		void Render() const override;
		void SetComponent(BaseComponent* comp) override ;
		BaseComponent* Clone() override;
	private:
		TextRenderer* m_pTextRenderer;
		TextMaterial* m_pMat;
	};

}


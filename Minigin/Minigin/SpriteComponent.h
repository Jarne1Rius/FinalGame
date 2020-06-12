#pragma once
#include "BaseComponent.h"
#include "Extra.h"

namespace Rius
{
	class TextureMaterial;
	class SpriteRenderer;
	class SpriteComponent final : public BaseComponent
	{
	public:
		SpriteComponent(TextureMaterial* textureBullet, const Rectangle2D& texCoordSizeOfTexture, float scale = 1);
		~SpriteComponent();
		SpriteComponent(const SpriteComponent& other);
		SpriteComponent(SpriteComponent&& other) noexcept = default;
		SpriteComponent& operator= (const SpriteComponent& other) = default;
		SpriteComponent& operator= (SpriteComponent&& other) = default;


		void Initialize() override;
		void Update(float deltaT) override;
		void Render() const override;
		BaseComponent* Clone() override;
	private:
		TextureMaterial* m_PMat;
		SpriteRenderer* m_Sprite;
		Rectangle2D m_TexCoord;
		float m_Scale;
	};

}

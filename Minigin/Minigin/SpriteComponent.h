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
		SpriteComponent(TextureMaterial* textureBullet, const Rectangle2D& texCoordSizeOfTexture);
		~SpriteComponent();
		void Initialize() override;
		void Update() override;
		void Render() const override;
		SpriteComponent* Cloning();
	private:
		TextureMaterial* m_PMat;
		SpriteRenderer* m_Sprite;
		Rectangle2D m_TexCoord;
	};

}

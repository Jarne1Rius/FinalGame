#pragma once
#include "BaseComponent.h"
#include "Extra.h"
namespace Rius
{
	class SpriteRenderer;
	class TextureMaterial;
	class WallComponent final :	public BaseComponent
	{
	public:
		WallComponent(glm::vec2 texCoordinateOffset, TextureMaterial* material,const Rectangle2D& start, float width, float height);
		~WallComponent();
		void Initialize() override;
		void Render() const override;
		void Update() override;
	private:
		SpriteRenderer* m_pSprite;
		TextureMaterial* m_PMat;
		glm::vec2 m_Offset;
		Rectangle2D m_StartPos;
		float m_Width, m_Height;
	};

}
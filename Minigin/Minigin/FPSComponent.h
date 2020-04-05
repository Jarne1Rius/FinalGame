#pragma once
#include "BaseComponent.h"
#include <string>
#include <memory>
#include "Transform.h"
#include "glm/glm.hpp"
namespace Rius
{
	class Font;
	class Texture2D;
	class Transform;
	class FPSComponent : public BaseComponent
	{
		
		public:
			FPSComponent(Font* font, const glm::vec2& position = { 0,0 });
			virtual ~FPSComponent();
			void Update() override;
			void Initialize() override;
			void Render() const override;
			void SetPosition(float x, float y);
			Rius::Transform GetTransform() const { return  m_Transform; }

		private:
			Rius::Transform m_Transform;
			int m_Frames;
			Font* m_pFont;
			Texture2D* m_Texture;
		
	};

}


#pragma once
#include "BaseComponent.h"
#include "Transform.h"
#include "glm/glm.hpp"

namespace Rius
{
	class TextureComponent :
		public BaseComponent
	{
	public:
		TextureComponent(const std::string& filename,const glm::vec2& position = {0,0});
		virtual ~TextureComponent();
		void Update() override;
		void Initialize() override;
		void Render() const override;

		void SetPosition(float x, float y);
	private:
		class Texture2D* m_pTexture;
		Transform m_Transform;

		void SetTexture(const std::string& filename);
	};

}


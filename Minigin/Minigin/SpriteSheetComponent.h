#pragma once
#include <glad/glad.h>
#include  <vector>
#include "BaseComponent.h"
#include "Extra.h"
#include "Texture2D.h"
#include <string>

namespace Rius
{
	class Shader;

	class SpriteSheetComponent : public BaseComponent
	{
	public:
		SpriteSheetComponent(Shader* shader, const Rectangle2D& destRectangle, int rows, int colms, float speed);
		~SpriteSheetComponent();
		void Initialize() override;
		void Render() const override;
		void Update() override;
		void SetTexture(Texture2D* texture);
		void SetTexture(const std::string& name);
		Rectangle2D GetRectangle() { return m_Rectangle2D; }
	private:
		Texture2D* m_pTexture2D;
		Shader* m_pShader;
		GLuint m_QuadVAO;
		std::vector<float> m_Vertices;
		Rectangle2D m_Rectangle2D;
		int m_Speed;
		int m_colms;
		int m_Rows;
		int m_CurrentFrame;
		
	};
}

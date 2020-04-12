#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Shader.h"
#include "BaseComponent.h"
#include <vector>
#include "Extra.h"

namespace Rius
{
	class Texture2D;
	class Shader;

	class SpriteRenderer : public BaseComponent
	{
	public:
		SpriteRenderer(Shader* shader,const Rectangle2D& destRectangle, const Rectangle2D& textCoord);
		~SpriteRenderer();
		void SetTexture(Texture2D* texture);
		void SetTexture(const std::string& name);
		void Initialize() override;
		void Update() override;
		void Render() const override;
		Rectangle2D GetRectangle()const  { return m_Rectangle2D; };
	private:
		Texture2D* m_pTexture2D;
		Shader* m_Shader;
		GLuint m_QuadVAO;
		std::vector<float> m_Vertices;
		Rectangle2D m_Rectangle2D;
		Rectangle2D m_TextCoord;

		void SetIndicesAndVertices();
	};
}


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
		SpriteSheetComponent(Shader* shader, const Rectangle2D& destRectangle, int rows, int colms, float timeNextFrame = 10, int firstFrame = 0, int totalFrames = 0);
		SpriteSheetComponent(Shader* shader, const Rectangle2D& destRectangle, int rows, int colms, float widthColms, float heightOfRows,glm::vec2& startPosition, float timeNextFrame = 10, int firstFrame = 0, int totalFrames = 0);
		~SpriteSheetComponent();
		SpriteSheetComponent(const SpriteSheetComponent& other);
		SpriteSheetComponent(SpriteSheetComponent&& other) noexcept = default;
		SpriteSheetComponent& operator= (const SpriteSheetComponent& other) = default;
		SpriteSheetComponent& operator= (SpriteSheetComponent&& other) = default;
		
		void Initialize() override;
		void Render() const override;
		void Update() override;
		void LateUpdate() override;
		void SetTexture(Texture2D* texture);
		void SetTexture(const std::string& name);
		void SetColor(Color newColor);
		BaseComponent* Clone() override;
		void SetComponent(BaseComponent* comp) override;
		Rectangle2D GetRectangle() const { return m_Rectangle2D; }
	private:
		Texture2D* m_pTexture2D;
		Shader* m_pShader;
		GLuint m_QuadVAO;
		GLuint m_VBO;
		GLuint m_EBO;
		std::vector<float> m_Vertices;
		std::vector<unsigned int> m_Indices;
		glm::mat4 m_ModelSpace;
		glm::vec4 m_Color;
		Rectangle2D m_Rectangle2D;
		Rectangle2D m_TextCoord;
		float m_TimeNextFrame;
		int m_Colms;
		int m_Rows;
		int m_CurrentFrame;
		int m_TotalFrames;
		float m_Sec;
		float m_WidthObject;
		float m_HeightObject;
		Rectangle2D m_SrcRect;
		void SetIndicesAndVertices();
	};
}

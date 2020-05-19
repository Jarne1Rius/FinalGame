#pragma once
#include <glad/glad.h>
#include  <vector>
#include "BaseComponent.h"
#include "Extra.h"
#include "Texture2D.h"
#include <string>

#include "Material.h"
#include "TextRenderer.h"
namespace Rius
{
	class Shader;

	struct SpriteTotal
	{
		std::string m_Name;
		int m_TotalFrames;
		int m_StartFrame;
		float m_TimeNextFrame;
		int m_Colms;
		int m_Rows;
		int m_FirstFrame = 0;
	};

	class SpriteSheetComponent : public BaseComponent
	{
	public:
		SpriteSheetComponent(Material* material, const Rectangle2D& destRectangle, bool isStatic, int rows, int colms, std::vector<SpriteTotal> totalAnimations);
		SpriteSheetComponent(Material* material,  const Rectangle2D& destRectangle, bool isStatic, int rows, int colms, float timeNextFrame = 10, int firstFrame = 0, int totalFrames = 0);
		SpriteSheetComponent(Material* material, const Rectangle2D& destRectangle, bool isStatic, int rows, int colms, float widthColms, float heightOfRows,glm::vec2& startPosition, float timeNextFrame = 10, int firstFrame = 0, int totalFrames = 0);
		~SpriteSheetComponent();
		SpriteSheetComponent(const SpriteSheetComponent& other);
		SpriteSheetComponent(SpriteSheetComponent&& other) noexcept = default;
		SpriteSheetComponent& operator= (const SpriteSheetComponent& other) = default;
		SpriteSheetComponent& operator= (SpriteSheetComponent&& other) = default;

		void SetAnimation(int animation);
		void SetAnimation(std::string name);
		void Initialize() override;
		void Render() const override;
		void Update() override;
		void LateUpdate() override;
		BaseComponent* Clone() override;
		void SetComponent(BaseComponent* comp) override;
		Rectangle2D GetRectangle() const { return m_Rectangle2D; }
	private:
		Material* m_pMaterial;
		bool m_Static;
		GLuint m_QuadVAO;
		GLuint m_VBO;
		GLuint m_EBO;
		std::vector<float> m_Vertices;
		std::vector<unsigned int> m_Indices;
		glm::mat4 m_ModelSpace;
		glm::vec4 m_Color;
		Rectangle2D m_Rectangle2D;
		Rectangle2D m_TextCoord;
		int m_Colms;
		int m_Rows;
		int m_CurrentFrame;
		float m_Sec;
		float m_WidthObject;
		float m_HeightObject;
		Rectangle2D m_SrcRect;
		std::vector<SpriteTotal> m_TotalAnimations;
		int m_CurrentAnimation;
		void SetIndicesAndVertices();
	};
}

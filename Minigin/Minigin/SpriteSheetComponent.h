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

	struct Animation
	{
		Animation(Rectangle2D texCoord, std::string name, int totalFrams, float timenext, int colms, int rows, int  firstframe = 0)
			:m_TexCoord(texCoord), m_Colms(colms), m_Rows(rows), m_FirstFrame(firstframe), m_TotalFrames(totalFrams), m_TimeNextFrame(timenext), m_Name(name)
		{};
		Rectangle2D m_TexCoord = {0,0,0,0};
		std::string m_Name = "";
		int m_TotalFrames = 0;
		float m_TimeNextFrame = 0;
		int m_Colms = 1;
		int m_Rows = 1;
		int m_FirstFrame = 0;
	};

	class SpriteSheetComponent : public BaseComponent
	{
	public:
		SpriteSheetComponent(Material* material, const Rectangle2D& destRectangle, bool isStatic, std::vector<Animation> totalAnimations);
		~SpriteSheetComponent();
		SpriteSheetComponent(const SpriteSheetComponent& other);
		SpriteSheetComponent(SpriteSheetComponent&& other) noexcept = default;
		SpriteSheetComponent& operator= (const SpriteSheetComponent& other) = default;
		SpriteSheetComponent& operator= (SpriteSheetComponent&& other) = default;

		void SetAnimation(int animation);
		void SetAnimation(std::string name);
		void Initialize() override;
		void Render() const override;
		void Update(float deltaT) override;
		void LateUpdate() override;
		BaseComponent* Clone() override;
		void SetComponent(BaseComponent* comp) override;
		Rectangle2D GetRectangle() const { return m_Rectangle2D; }
		void ResetSpriteSheet(Material* material, const Rectangle2D& destRectangle, bool isStatic, int rows, int colms, std::vector<Animation> totalAnimations);
		bool CheckOneCicle();
		void SetFrame(int firstFrame) { m_TotalAnimations[m_CurrentAnimation].m_FirstFrame = firstFrame; m_CurrentFrame = firstFrame; };
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
		float m_SecCicle;
		int m_CurrentFrame;
		float m_Sec;
		float m_WidthObject;
		float m_HeightObject;
		Rectangle2D m_SrcRect;
		std::vector<Animation> m_TotalAnimations;
		int m_CurrentAnimation;
		void SetIndicesAndVertices();
		void SetRightTexCoord();
	};
}

#pragma once
#include <glad/glad.h>
#include  <vector>
#include "BaseComponent.h"
#include "Extra.h"
#include <string>

#include "Material.h"
namespace Rius
{
	class Shader;

	struct Animation
	{
		Animation(Rectangle2D texCoord, std::string name, int totalFrames = 1, float timenext = 0.1f, int colms = 1, int rows = 1, int  firstframe = 0)
			:texCoord(texCoord), colms(colms), rows(rows), firstFrame(firstframe), totalFrames(totalFrames), timeNextFrame(timenext), name(name)
		{};
		Rectangle2D texCoord = { 0,0,1,1 };
		std::string name = "";
		int totalFrames;
		float timeNextFrame;
		int colms;
		int rows;
		int firstFrame;
	};

	class SpriteSheetComponent final : public BaseComponent
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
		BaseComponent* Clone() override;
		void SetComponent(BaseComponent* comp) override;
		Rectangle2D GetRectangle() const { return m_Rectangle2D; }
		void ResetSpriteSheet(Material* material, const Rectangle2D& destRectangle, bool isStatic, std::vector<Animation> totalAnimations);
		bool CheckOneCicle();
		void SetFrame(int firstFrame) { m_TotalAnimations[m_CurrentAnimation].firstFrame = firstFrame; m_CurrentFrame = firstFrame; };
	private:
		bool m_Static;
		int m_CurrentAnimation;
		int m_CurrentFrame;

		float m_SecCicle;
		float m_Sec;

		Material* m_pMaterial;
		GLuint m_QuadVAO;
		GLuint m_VBO;
		GLuint m_EBO;

		std::vector<float> m_Vertices;
		std::vector<unsigned int> m_Indices;
		glm::mat4 m_ModelSpace;

		Rectangle2D m_Rectangle2D;
		Rectangle2D m_TextCoord;
		Rectangle2D m_SrcRect;
		std::vector<Animation> m_TotalAnimations;

		void SetIndicesAndVertices();
		void SetRightTexCoord();
		void UpdateIndicesAndVertices();
	};
}

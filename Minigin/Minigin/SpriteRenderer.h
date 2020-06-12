#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Shader.h"
#include "BaseComponent.h"
#include <vector>
#include "Extra.h"
#include "Transform.h"
namespace Rius
{
	class Material;
	class Texture2D;

	class SpriteRenderer
	{
	public:
		SpriteRenderer(glm::vec2 position, Material* material, const Rectangle2D& destRectangle, bool isStatic = true, const Rectangle2D& textCoord = { 0,0,1,1 });
		SpriteRenderer(glm::vec2 position, Material* material, const Rectangle2D& destRectangle, const float widthTile, float heightTile, bool isStatic = true);
		~SpriteRenderer();
		SpriteRenderer(const SpriteRenderer& other);
		SpriteRenderer(SpriteRenderer&& other) noexcept = default;
		SpriteRenderer& operator= (const SpriteRenderer& other) = default;
		SpriteRenderer& operator= (SpriteRenderer&& other) = default;

		void Initialize();
		void Update();
		void LateUpdate(const glm::vec3& pos);
		void Render() const;
		Rectangle2D GetRectangle()const { return m_Rectangle2D; };
	private:
		Material* m_pMaterial;
		bool m_Static = false;
		GLuint m_QuadVAO;
		std::vector<float> m_Vertices;
		std::vector<unsigned int> m_Indices;
		glm::mat4 m_ModelSpace;
		glm::vec4 m_Color;
		Rectangle2D m_Rectangle2D;
		Rectangle2D m_TextCoord;
		GLuint m_VBO;
		GLuint m_EBO;
		glm::vec2 m_Pos;
		void SetIndicesAndVertices();
	};
}


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

	class SpriteRendererComponent : public BaseComponent
	{
	public:
		SpriteRendererComponent(Shader* shader,const Rectangle2D& destRectangle, const Rectangle2D& textCoord = {0,0,1,1});
		~SpriteRendererComponent();
		SpriteRendererComponent(const SpriteRendererComponent& other);
		SpriteRendererComponent(SpriteRendererComponent&& other) noexcept = default;
		SpriteRendererComponent& operator= (const SpriteRendererComponent& other) = default;
		SpriteRendererComponent& operator= (SpriteRendererComponent&& other) = default;
		BaseComponent* Clone() override;
		void SetComponent(BaseComponent* comp) override;
		
		void SetTexture(Texture2D* texture);
		void SetTexture(const std::string& name);
		void Initialize() override;
		void Update() override;
		void Render() const override;
		void SetColor(Color newColor);
		Rectangle2D GetRectangle()const  { return m_Rectangle2D; };
	private:
		Texture2D* m_pTexture2D;
		Shader* m_pShader;
		GLuint m_QuadVAO;
		std::vector<float> m_Vertices;
		std::vector<unsigned int> m_Indices;
		glm::mat4 m_ModelSpace;
		glm::vec4 m_Color;
		Rectangle2D m_Rectangle2D;
		Rectangle2D m_TextCoord;
		GLuint m_VBO;
		GLuint m_EBO;
		void SetIndicesAndVertices();
	};
}


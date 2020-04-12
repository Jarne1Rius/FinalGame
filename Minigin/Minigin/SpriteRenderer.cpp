#include "MiniginPCH.h"
#include "SpriteRenderer.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Texture2D.h"
#include "GameObject.h"
#include "ResourceManager.h"
Rius::SpriteRenderer::SpriteRenderer(Shader* shader,const Rectangle2D& rectangle, const Rectangle2D& textCoord)
    :m_Rectangle2D(rectangle),m_Vertices(),m_QuadVAO(),m_Shader(),m_pTexture2D(nullptr),m_TextCoord(textCoord)
{
    m_Shader = shader;
    Initialize();
}

Rius::SpriteRenderer::~SpriteRenderer()
{
    m_Vertices.clear();
    glDeleteVertexArrays(1, &this->m_QuadVAO);
}

void Rius::SpriteRenderer::SetTexture(Texture2D* texture)
{
    m_pTexture2D = texture;
}

void Rius::SpriteRenderer::SetTexture(const std::string& name)
{
    m_pTexture2D = ResourceManager::GetInstance().GetTexture(name);
}

void Rius::SpriteRenderer::Initialize()
{
    // Configure m_VAO/m_VBO
    SetIndicesAndVertices();
    glGenVertexArrays(1, &this->m_QuadVAO);
    glGenBuffers(1, &m_VBO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(float),  &m_Vertices[0], GL_STATIC_DRAW);

    glBindVertexArray(this->m_QuadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Rius::SpriteRenderer::Update()
{
}
void Rius::SpriteRenderer::Render() const
{
    this->m_Shader->Use();
    glm::mat4 model;
    model = glm::translate(model, glm::vec3(0,0, 0.0f));
    model = glm::scale(model, glm::vec3(1,1, 1.0f));
    this->m_Shader->SetMat4("model", model);
    this->m_Shader->SetVec3("spriteColor", 1,1,1);
    glActiveTexture(GL_TEXTURE0);
	if(m_pTexture2D != nullptr)
		m_pTexture2D->Bind();
    glBindVertexArray(this->m_QuadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    
}

void Rius::SpriteRenderer::SetIndicesAndVertices()
{
    m_Vertices.clear();
    m_Vertices.resize(24);
    //TopRight
    m_Vertices[0] = (m_Rectangle2D.pos.x );
    m_Vertices[1] = (m_Rectangle2D.pos.y + m_Rectangle2D.height);
    m_Vertices[2] = (m_TextCoord.pos.x);
    m_Vertices[3] = (m_TextCoord.pos.y + m_TextCoord.height);

    //BottomRight
    m_Vertices[4] = (m_Rectangle2D.pos.x + m_Rectangle2D.width);
    m_Vertices[5] = (m_Rectangle2D.pos.y);
    m_Vertices[6] = (m_TextCoord.pos.x + m_TextCoord.width);
    m_Vertices[7] = (m_TextCoord.pos.y);

    //BottomLeft
    m_Vertices[8] = (m_Rectangle2D.pos.x);
    m_Vertices[9] = (m_Rectangle2D.pos.y);
    m_Vertices[10] = (m_TextCoord.pos.x);
    m_Vertices[11] = (m_TextCoord.pos.y);
	
    //TopLeft
    m_Vertices[12] = (m_Rectangle2D.pos.x);
    m_Vertices[13] = (m_Rectangle2D.pos.y + m_Rectangle2D.height);
    m_Vertices[14] = (m_TextCoord.pos.x);
    m_Vertices[15] = (m_TextCoord.pos.y + m_TextCoord.height);

    m_Vertices[16] = (m_Rectangle2D.pos.x + m_Rectangle2D.width);
    m_Vertices[17] = (m_Rectangle2D.pos.y + m_Rectangle2D.height);
    m_Vertices[18] = (m_TextCoord.pos.x + m_TextCoord.width);
    m_Vertices[19] = (m_TextCoord.pos.y + m_TextCoord.height);
	
    m_Vertices[20] = (m_Rectangle2D.pos.x + m_Rectangle2D.width);
    m_Vertices[21] = (m_Rectangle2D.pos.y);
    m_Vertices[22] = (m_TextCoord.pos.x + m_TextCoord.width);
    m_Vertices[23] = (m_TextCoord.pos.y);

}



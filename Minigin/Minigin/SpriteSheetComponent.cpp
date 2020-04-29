#include "MiniginPCH.h"
#include "SpriteSheetComponent.h"
#include "Shader.h"
#include <glm/gtc/matrix_transform.hpp>

#include "Minigin.h"
#include "time.h"
#include "ResourceManager.h"
#include "GameObject.h"

Rius::SpriteSheetComponent::SpriteSheetComponent(Shader* shader, const Rectangle2D& destRectangle, int rows, int colms, float timeNextFrame, int firstFrame, int totalFrames)
	:m_Vertices(), m_Rectangle2D(destRectangle), m_QuadVAO(), m_pShader(shader), m_pTexture2D(), m_TimeNextFrame(timeNextFrame), m_Colms(colms), m_Rows(rows), m_CurrentFrame(firstFrame)
	, m_TextCoord(0, 0, 1, 1), m_Sec(0), m_WidthObject(), m_HeightObject(), m_SrcRect(0, 0, 1, 1), m_VBO(), m_TotalFrames((totalFrames == 0) ? colms * rows : totalFrames)
{
	m_WidthObject = 1.f / colms;
	m_HeightObject = 1.f / rows;
	int colm = (m_CurrentFrame % m_Colms);
	int row = int(m_CurrentFrame / m_Colms);
	glm::vec2 pos{ m_WidthObject * colm, m_HeightObject * row };
	m_TextCoord = Rectangle2D{ pos.x,pos.y,m_WidthObject,m_HeightObject };
}

Rius::SpriteSheetComponent::SpriteSheetComponent(Shader* shader, const Rectangle2D& destRectangle, int rows, int colms, float widthColms, float heightOfRows, glm::vec2& startPosition, float timeNextFrame, int firstFrame, int totalFrames)
	:m_Vertices(), m_Rectangle2D(destRectangle), m_QuadVAO(), m_pShader(shader), m_pTexture2D(), m_TimeNextFrame(timeNextFrame), m_Colms(colms), m_Rows(rows), m_CurrentFrame(firstFrame), m_TextCoord(0, 0, 1, 1)
	, m_SrcRect(startPosition, widthColms, heightOfRows), m_Sec(0), m_WidthObject(), m_HeightObject(), m_TotalFrames(), m_VBO()
{
	m_WidthObject = m_SrcRect.width / colms;
	m_HeightObject = m_SrcRect.height / rows;
	int colm = (m_CurrentFrame % m_Colms);
	int row = int(m_CurrentFrame / m_Colms);
	glm::vec2 pos{ m_WidthObject * colm, m_HeightObject * row };
	m_TextCoord = Rectangle2D{ pos.x,pos.y,m_WidthObject,m_HeightObject };
	//Initialize();
}

Rius::SpriteSheetComponent::~SpriteSheetComponent()
{
	m_Vertices.clear();
	glDeleteVertexArrays(1, &this->m_QuadVAO);
}

Rius::SpriteSheetComponent::SpriteSheetComponent(const SpriteSheetComponent& other)
	:m_Rectangle2D(0,0,0,0),m_TextCoord(0,0,0,0), m_SrcRect(0,0,0,0)
{
	this->m_pGameObject = other.m_pGameObject;
	this->m_Vertices = other.m_Vertices;
	this->m_Rectangle2D = other.m_Rectangle2D;
	this->m_TextCoord = other.m_TextCoord;
	this->m_Colms = other.m_Colms;
	this->m_Color = other.m_Color;
	this->m_Indices = other.m_Indices;
	this->m_CurrentFrame = other.m_CurrentFrame;
	this->m_pTexture2D = other.m_pTexture2D;
	this->m_EBO = other.m_EBO;
	this->m_TotalFrames = other.m_TotalFrames;
	this->m_TimeNextFrame = other.m_TimeNextFrame;
	this->m_ModelSpace = other.m_ModelSpace;
	this->m_HeightObject = other.m_HeightObject;
	this->m_QuadVAO = other.m_QuadVAO;
	this->m_pShader = other.m_pShader;
	this->m_WidthObject = other.m_WidthObject;
	this->m_VBO = other.m_VBO;
	this->m_SrcRect = other.m_SrcRect;
	this->m_Sec = other.m_Sec;
}

void Rius::SpriteSheetComponent::Initialize()
{
	// Configure m_VAO/m_VBO
	SetIndicesAndVertices();
	glGenVertexArrays(1, &m_QuadVAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);
	glBindVertexArray(m_QuadVAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(float), &m_Vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), &m_Indices[0], GL_STATIC_DRAW);

	glBindVertexArray(this->m_QuadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	this->m_pShader->SetVec3("spriteColor", 1, 1, 1);
	Update();
}

void Rius::SpriteSheetComponent::Render() const
{
	this->m_pShader->Use();
	this->m_pShader->SetMat4("model", m_ModelSpace);
	glActiveTexture(GL_TEXTURE0);
	if (m_pTexture2D != nullptr)
		m_pTexture2D->Bind();
	glBindVertexArray(this->m_QuadVAO);
	glDrawElements(GL_TRIANGLES, GLsizei(m_Indices.size())
		, GL_UNSIGNED_INT, static_cast<void*>(nullptr));
	glBindVertexArray(0);
}

void Rius::SpriteSheetComponent::Update()
{
	m_ModelSpace = glm::mat4();
	m_ModelSpace = glm::translate(m_ModelSpace, m_pGameObject->GetTransform().GetPosition());
	m_ModelSpace = glm::scale(m_ModelSpace, glm::vec3(1, 1, 1.0f));

}

void Rius::SpriteSheetComponent::LateUpdate()
{
	m_Sec += Time::m_DeltaTime;
	while (m_Sec >= m_TimeNextFrame)
	{
		m_Sec -= (m_TimeNextFrame);
		m_CurrentFrame++;
		m_CurrentFrame %= m_TotalFrames;
		int colms = (m_CurrentFrame % m_Colms);
		int rows = int(m_CurrentFrame / m_Colms);
		glm::vec2 pos{ m_WidthObject * colms, m_HeightObject * rows };
		m_TextCoord.pos = pos;
		Initialize();
	}
}

void Rius::SpriteSheetComponent::SetTexture(Texture2D* texture)
{
	m_pTexture2D = texture;

}

void Rius::SpriteSheetComponent::SetTexture(const std::string& name)
{
	m_pTexture2D = ResourceManager::GetTexture(name);
}

void Rius::SpriteSheetComponent::SetColor(Color newColor)
{
	m_Color = newColor.GetVec4();
	this->m_pShader->Use().SetVec4("Color", m_Color);
}

Rius::BaseComponent* Rius::SpriteSheetComponent::Clone()
{
	return new SpriteSheetComponent{ *this };
}

void Rius::SpriteSheetComponent::SetComponent(BaseComponent* comp)
{
	SpriteSheetComponent* component = static_cast <SpriteSheetComponent*> (comp);
	this->m_pGameObject = component->m_pGameObject;
	this->m_Vertices = component->m_Vertices;
	this->m_Rectangle2D = component->m_Rectangle2D;
	this->m_TextCoord = component->m_TextCoord;
	this->m_Colms = component->m_Colms;
	this->m_Color = component->m_Color;
	this->m_Indices = component->m_Indices;
	this->m_CurrentFrame = component->m_CurrentFrame;
	this->m_pTexture2D = component->m_pTexture2D;
	this->m_EBO = component->m_EBO;
	this->m_TotalFrames = component->m_TotalFrames;
	this->m_TimeNextFrame = component->m_TimeNextFrame;
	this->m_ModelSpace = component->m_ModelSpace;
	this->m_HeightObject = component->m_HeightObject;
	this->m_QuadVAO = component->m_QuadVAO;
	this->m_pShader = component->m_pShader;
	this->m_WidthObject = component->m_WidthObject;
	this->m_VBO = component->m_VBO;
	this->m_SrcRect = component->m_SrcRect;
	this->m_Sec = component->m_Sec;	
}

void Rius::SpriteSheetComponent::SetIndicesAndVertices()
{
	m_Vertices.clear();
	m_Vertices.resize(24);
	//TopRight
	m_Vertices[0] = (m_Rectangle2D.pos.x + m_Rectangle2D.width / 2.f);
	m_Vertices[1] = Minigin::m_Height - (m_Rectangle2D.pos.y + m_Rectangle2D.height / 2.f);
	m_Vertices[2] = (m_TextCoord.pos.x);
	m_Vertices[3] = (m_TextCoord.pos.y);

	//BottomRight
	m_Vertices[4] = (m_Rectangle2D.pos.x + m_Rectangle2D.width / 2.f);
	m_Vertices[5] = Minigin::m_Height - (m_Rectangle2D.pos.y - m_Rectangle2D.height / 2.f);
	m_Vertices[6] = (m_TextCoord.pos.x);
	m_Vertices[7] = (m_TextCoord.pos.y + m_TextCoord.height);

	//BottomLeft
	m_Vertices[8] = (m_Rectangle2D.pos.x - m_Rectangle2D.width / 2.f);
	m_Vertices[9] = Minigin::m_Height - (m_Rectangle2D.pos.y - m_Rectangle2D.height / 2.f);
	m_Vertices[10] = (m_TextCoord.pos.x + m_TextCoord.width);
	m_Vertices[11] = (m_TextCoord.pos.y + m_TextCoord.height);

	//TopLeft
	m_Vertices[12] = (m_Rectangle2D.pos.x - m_Rectangle2D.width / 2.f);
	m_Vertices[13] = Minigin::m_Height - (m_Rectangle2D.pos.y + m_Rectangle2D.height / 2.f);
	m_Vertices[14] = (m_TextCoord.pos.x + m_TextCoord.width);
	m_Vertices[15] = (m_TextCoord.pos.y);
	m_Indices = std::vector<unsigned int>{ 0, 1, 3 ,1,2,3 };
}

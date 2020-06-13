#include "MiniginPCH.h"
#include "SpriteSheetComponent.h"
#include "Shader.h"
#include <glm/gtc/matrix_transform.hpp>

#include "Minigin.h"
#include "time.h"
#include "ResourceManager.h"
#include "GameObject.h"

Rius::SpriteSheetComponent::SpriteSheetComponent(Material* material, const Rectangle2D& destRectangle, bool isStatic, std::vector<Animation> totalAnimations)
	:m_Vertices(), m_Rectangle2D(destRectangle), m_Static(isStatic), m_QuadVAO(), m_pMaterial(material), m_CurrentAnimation(totalAnimations[0].m_FirstFrame)
	, m_TextCoord(0, 0, 1, 1), m_Sec(0), m_WidthObject(), m_HeightObject(), m_SrcRect(0, 0, 1, 1), m_VBO(), m_Indices(), m_ModelSpace(), m_Color(), m_EBO(), m_TotalAnimations(totalAnimations), m_CurrentFrame(), m_SecCicle()
{
	SetAnimation(0);
}




Rius::SpriteSheetComponent::~SpriteSheetComponent()
{
	m_Vertices.clear();
	glDeleteVertexArrays(1, &this->m_QuadVAO);
}

Rius::SpriteSheetComponent::SpriteSheetComponent(const SpriteSheetComponent& other)
	:m_Rectangle2D(0, 0, 0, 0), m_TextCoord(0, 0, 0, 0), m_SrcRect(0, 0, 0, 0)
{
	this->m_pGameObject = other.m_pGameObject;
	this->m_Vertices = other.m_Vertices;
	this->m_Rectangle2D = other.m_Rectangle2D;
	this->m_TextCoord = other.m_TextCoord;
	this->m_Color = other.m_Color;
	this->m_Indices = other.m_Indices;
	this->m_CurrentFrame = other.m_CurrentFrame;
	this->m_EBO = other.m_EBO;
	this->m_ModelSpace = other.m_ModelSpace;
	this->m_HeightObject = other.m_HeightObject;
	this->m_QuadVAO = other.m_QuadVAO;
	this->m_pMaterial = other.m_pMaterial;
	this->m_WidthObject = other.m_WidthObject;
	this->m_VBO = other.m_VBO;
	this->m_SrcRect = other.m_SrcRect;
	this->m_Sec = other.m_Sec;
}

void Rius::SpriteSheetComponent::SetAnimation(int animation)
{
	m_Sec = 0;
	m_CurrentAnimation = animation;
	m_CurrentFrame = m_TotalAnimations[m_CurrentAnimation].m_FirstFrame;
	SetRightTexCoord();
}

void Rius::SpriteSheetComponent::SetAnimation(std::string name)
{
	int i{};
	for (Animation animation : m_TotalAnimations)
	{
		if (name == animation.m_Name)
		{
			m_SecCicle = 0;
			m_Sec = 0;
			m_CurrentAnimation = i;
			m_CurrentFrame = animation.m_FirstFrame;
		}
		i++;
	}
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
	//	m_ModelSpace = glm::mat4();
	//	m_ModelSpace = glm::translate(m_ModelSpace, m_pGameObject->GetTransform().GetPosition());
	//	m_ModelSpace = glm::scale(m_ModelSpace, glm::vec3(-1, 1, 1.0f));
	//	m_pMaterial->SetModelSpace(m_ModelSpace);
}

void Rius::SpriteSheetComponent::Render() const
{

	m_pMaterial->UpdateVariables();
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(this->m_QuadVAO);
	glDrawElements(GL_TRIANGLES, GLsizei(m_Indices.size())
		, GL_UNSIGNED_INT, static_cast<void*>(nullptr));
	glBindVertexArray(0);
}

void Rius::SpriteSheetComponent::Update(float deltaT)
{

}

void Rius::SpriteSheetComponent::LateUpdate()
{

	if (!m_Static)
	{
		m_ModelSpace = glm::mat4();
		m_ModelSpace = glm::translate(m_ModelSpace, m_pGameObject->GetTransform().GetPosition());
		m_ModelSpace = glm::scale(m_ModelSpace, m_pGameObject->GetTransform().GetScale());
		m_pMaterial->SetModelSpace(m_ModelSpace);
	}

	Animation& current = m_TotalAnimations[m_CurrentAnimation];


	m_Sec += Time::m_DeltaTime;
	m_SecCicle += Time::m_DeltaTime;
	while (m_Sec >= current.m_TimeNextFrame)
	{
		m_Sec -= (current.m_TimeNextFrame);
		SetRightTexCoord();
	}
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
	this->m_Color = component->m_Color;
	this->m_Indices = component->m_Indices;
	this->m_CurrentFrame = component->m_CurrentFrame;
	this->m_EBO = component->m_EBO;
	this->m_ModelSpace = component->m_ModelSpace;
	this->m_HeightObject = component->m_HeightObject;
	this->m_QuadVAO = component->m_QuadVAO;
	this->m_pMaterial = component->m_pMaterial;
	this->m_WidthObject = component->m_WidthObject;
	this->m_VBO = component->m_VBO;
	this->m_SrcRect = component->m_SrcRect;
	this->m_Sec = component->m_Sec;
}

void Rius::SpriteSheetComponent::ResetSpriteSheet(Material* material, const Rectangle2D& destRectangle, bool isStatic,
	int rows, int colms, std::vector<Animation> totalAnimations)
{
	m_Rectangle2D = destRectangle;
	m_Static = isStatic;
	m_CurrentFrame = totalAnimations[0].m_FirstFrame;
	m_TextCoord = { 0,0,1,1 };
	m_SrcRect = { 0,0,1,1 };
	m_TotalAnimations = totalAnimations;
	SetIndicesAndVertices();
	m_CurrentAnimation = 0;

}

bool Rius::SpriteSheetComponent::CheckOneCicle()
{
	return (m_SecCicle >= m_TotalAnimations[m_CurrentAnimation].m_TotalFrames * m_TotalAnimations[m_CurrentAnimation].m_TimeNextFrame);
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

void Rius::SpriteSheetComponent::SetRightTexCoord()
{
	Animation& current = m_TotalAnimations[m_CurrentAnimation];
	m_CurrentFrame++;
	m_CurrentFrame %= current.m_TotalFrames;
	m_CurrentFrame += current.m_FirstFrame;

	m_TextCoord.width = current.m_TexCoord.width / current.m_Colms;
	m_TextCoord.height = current.m_TexCoord.height / current.m_Rows;

	float colms = (m_CurrentFrame % current.m_Colms) * m_TextCoord.width;
	float rows = (m_CurrentFrame / current.m_Colms) * m_TextCoord.height;

	glm::vec2 pos{ colms + current.m_TexCoord.pos.x ,rows + current.m_TexCoord.pos.y };
	m_TextCoord.pos = pos;
	Initialize();
}

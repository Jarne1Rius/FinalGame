#include "MiniginPCH.h"
#include "SpriteRendererComponent.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Texture2D.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Minigin.h"
#include "Material.h"
Rius::SpriteRendererComponent::SpriteRendererComponent(Material* material,  const Rectangle2D& rectangle, bool isStatic, const Rectangle2D& textCoord)
	:m_Rectangle2D(rectangle), m_Vertices(), m_QuadVAO(), m_pMaterial(material), m_TextCoord(textCoord), m_Static(isStatic),m_EBO(),m_ModelSpace(),m_VBO(),m_Color(),m_Indices()
{
}

Rius::SpriteRendererComponent::SpriteRendererComponent(Material* material, const Rectangle2D& destRectangle, const float widthTile, float heightTile, bool isStatic)
	: m_Rectangle2D(destRectangle), m_Vertices(), m_QuadVAO(), m_pMaterial(material), m_TextCoord(0,0,0,0), m_Static(isStatic),m_EBO(),m_ModelSpace(),m_VBO(),m_Color(),m_Indices()
{
	Rectangle2D textCoord{};
	textCoord.pos = { 0,0 };
	textCoord.height = destRectangle.height / heightTile;
	textCoord.width = destRectangle.width / widthTile;
	m_TextCoord = textCoord;
}

Rius::SpriteRendererComponent::~SpriteRendererComponent()
{
	m_Vertices.clear();
	glDeleteVertexArrays(1, &this->m_QuadVAO);
}

Rius::SpriteRendererComponent::SpriteRendererComponent(const SpriteRendererComponent& other)
	: m_Rectangle2D(0, 0, 0, 0), m_TextCoord(0, 0, 0, 0)
{
	this->m_pGameObject = other.m_pGameObject;
	this->m_Vertices = other.m_Vertices;
	this->m_Rectangle2D = other.m_Rectangle2D;
	this->m_TextCoord = other.m_TextCoord;
	this->m_Color = other.m_Color;
	this->m_Indices = other.m_Indices;
	this->m_EBO = other.m_EBO;
	this->m_ModelSpace = other.m_ModelSpace;
	this->m_QuadVAO = other.m_QuadVAO;
	this->m_pMaterial = other.m_pMaterial;
	this->m_VBO = other.m_VBO;
	this->m_Static = other.m_Static;
}

Rius::BaseComponent* Rius::SpriteRendererComponent::Clone()
{
	return new SpriteRendererComponent{ *this };
}

void Rius::SpriteRendererComponent::SetComponent(BaseComponent* comp)
{
	SpriteRendererComponent* component = static_cast <SpriteRendererComponent*> (comp);
	this->m_pGameObject = component->m_pGameObject;
	this->m_Vertices = component->m_Vertices;
	this->m_Rectangle2D = component->m_Rectangle2D;
	this->m_TextCoord = component->m_TextCoord;
	this->m_Color = component->m_Color;
	this->m_Indices = component->m_Indices;
	this->m_EBO = component->m_EBO;
	this->m_ModelSpace = component->m_ModelSpace;
	this->m_QuadVAO = component->m_QuadVAO;
	this->m_pMaterial = component->m_pMaterial;
	this->m_VBO = component->m_VBO;
	this->m_Static = component->m_Static;
}

void Rius::SpriteRendererComponent::Initialize()
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
	m_ModelSpace = glm::mat4();
	m_ModelSpace = glm::translate(m_ModelSpace, m_pGameObject->GetTransform().GetPosition());
	m_ModelSpace = glm::scale(m_ModelSpace, glm::vec3(1, 1, 1.0f));
	m_pMaterial->SetModelSpace(m_ModelSpace);
}

void Rius::SpriteRendererComponent::Update()
{
}

void Rius::SpriteRendererComponent::LateUpdate()
{
	if (!m_Static)
	{
		m_ModelSpace = glm::mat4();
		m_ModelSpace = glm::translate(m_ModelSpace, m_pGameObject->GetTransform().GetPosition());
		m_ModelSpace = glm::scale(m_ModelSpace, glm::vec3(1, 1, 1.0f));
		m_pMaterial->SetModelSpace(m_ModelSpace);
	}
}

void Rius::SpriteRendererComponent::Render() const
{
	m_pMaterial->UpdateVariables();
	glBindVertexArray(this->m_QuadVAO);
	glDrawElements(GL_TRIANGLES, GLsizei(m_Indices.size()), GL_UNSIGNED_INT, static_cast<void*>(nullptr));
	glBindVertexArray(0);

}
void Rius::SpriteRendererComponent::SetIndicesAndVertices()
{
	m_Vertices.clear();
	m_Vertices.resize(24);
	//TopRight
	m_Vertices[0] = (m_Rectangle2D.pos.x + m_Rectangle2D.width );
	m_Vertices[1] = Minigin::m_Height - (m_Rectangle2D.pos.y + m_Rectangle2D.height );
	m_Vertices[2] = (m_TextCoord.pos.x);
	m_Vertices[3] = (m_TextCoord.pos.y);

	//BottomRight
	m_Vertices[4] = (m_Rectangle2D.pos.x + m_Rectangle2D.width );
	m_Vertices[5] = Minigin::m_Height - (m_Rectangle2D.pos.y);//- m_Rectangle2D.height / 2.f);
	m_Vertices[6] = (m_TextCoord.pos.x);
	m_Vertices[7] = (m_TextCoord.pos.y + m_TextCoord.height);

	//BottomLeft
	m_Vertices[8] = (m_Rectangle2D.pos.x);// -m_Rectangle2D.width / 2.f);
	m_Vertices[9] = Minigin::m_Height - (m_Rectangle2D.pos.y);// -m_Rectangle2D.height / 2.f);
	m_Vertices[10] = (m_TextCoord.pos.x + m_TextCoord.width);
	m_Vertices[11] = (m_TextCoord.pos.y + m_TextCoord.height);

	//TopLeft
	m_Vertices[12] = (m_Rectangle2D.pos.x);// -m_Rectangle2D.width / 2.f);
	m_Vertices[13] = Minigin::m_Height - (m_Rectangle2D.pos.y + m_Rectangle2D.height );
	m_Vertices[14] = (m_TextCoord.pos.x + m_TextCoord.width);
	m_Vertices[15] = (m_TextCoord.pos.y);
	m_Indices = std::vector<unsigned int>{ 0, 1, 3 ,1,2,3 };
}



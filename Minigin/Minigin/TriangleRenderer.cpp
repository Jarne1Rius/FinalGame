#include "MiniginPCH.h"
#include "TriangleRenderer.h"

Rius::TriangleRenderer::TriangleRenderer(const std::vector<glm::vec2>& triangle,
	const std::vector<glm::vec2>& textCoord)
	:m_Triangle(triangle), m_TextCoord(textCoord),m_Material(),m_Vertices(),m_Indices(),m_EBO(),m_VBO(),m_VAO()
{
}

Rius::TriangleRenderer::~TriangleRenderer()
{
	SetIndicesAndVertices();

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	//Positions
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(float), &m_Vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(int), &m_Indices[0], GL_STATIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
}

void Rius::TriangleRenderer::Initialize()
{
	m_Material->Update(GetGameObject()->GetTransform());
}

void Rius::TriangleRenderer::Update()
{
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_Indices.size()), GL_UNSIGNED_INT, static_cast<void*>(nullptr));
	m_Material->Render();
}

void Rius::TriangleRenderer::Render() const
{
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_Indices.size()), GL_UNSIGNED_INT, static_cast<void*>(nullptr));
	m_Material->Render();
}

void Rius::TriangleRenderer::SetIndicesAndVertices()
{
	m_Vertices.resize(15);
	//TopRight
	m_Vertices[0] = m_Triangle[0].x;
	m_Vertices[1] = m_Triangle[0].y;
	m_Vertices[2] = 0;
	m_Vertices[3] = m_TextCoord[0].x;
	m_Vertices[4] = m_TextCoord[0].y;
	//TopRight
	m_Vertices[5] = m_Triangle[1].x;
	m_Vertices[6] = m_Triangle[1].y;
	m_Vertices[7] = 0;
	m_Vertices[8] = m_TextCoord[1].x;
	m_Vertices[9] = m_TextCoord[1].y;
	//TopRight
	m_Vertices[10] = m_Triangle[2].x;
	m_Vertices[11] = m_Triangle[2].y;
	m_Vertices[12] = 0;
	m_Vertices[13] = m_TextCoord[2].x;
	m_Vertices[14] = m_TextCoord[2].y;
}

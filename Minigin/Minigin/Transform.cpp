#include "MiniginPCH.h"
#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>

void Rius::Transform::Update()
{
	//m_TransformMatrix = m_Position * m_Rotation * m_Scale;
	m_TransformMatrix = glm::mat4{ 1.0f };
	m_TransformMatrix = glm::translate(m_TransformMatrix,m_Position);
	m_TransformMatrix = glm::(m_TransformMatrix, m_Rotation);
}

const glm::vec3& Rius::Transform::GetPosition() const
{
}

void Rius::Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void Rius::Transform::SetPosition(const glm::vec3& pos)
{
	m_Position = pos;
}

void Rius::Transform::SetRotation(glm::vec3& rotation)
{
	m_Rotation = rotation;
}

void Rius::Transform::SetRotation(float x, float y, float z)
{
}

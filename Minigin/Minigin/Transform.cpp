#include "MiniginPCH.h"
#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Minigin.h"

Rius::Transform::Transform()
	: m_Position(0, 0, 0), m_XAngle(0), m_YAngle(0), m_ZAngle(0), m_Scale(1, 1, 1)
{
}

Rius::Transform::Transform(const glm::vec3& position, const glm::vec3& scale)
	: m_Position(position), m_XAngle(0), m_YAngle(0), m_ZAngle(0), m_Scale(scale)
{
}

Rius::Transform::Transform(const glm::vec3& position, float xAngle, float yAngle, float zAngle)
	: m_Position(position), m_XAngle(xAngle), m_YAngle(yAngle), m_ZAngle(zAngle), m_Scale(1, 1, 1)
{
}

Rius::Transform::Transform(const glm::vec3& position, float xAngle, float yAngle, float zAngle, const glm::vec3& scale)
	: m_Position(position), m_XAngle(xAngle), m_YAngle(yAngle), m_ZAngle(zAngle), m_Scale(scale)
{
}

glm::vec3 Rius::Transform::GetPosition() const
{
	glm::vec3 newPos = glm::vec3(m_Position);
	return newPos;
}

void Rius::Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y =  - y;
	m_Position.z = z;
}

void Rius::Transform::SetPosition(const glm::vec3& pos)
{
	m_Position = pos;
}

glm::mat4& Rius::Transform::GetMatrix()
{
	m_TransformMatrix = glm::mat4{ 1.0f };
	m_TransformMatrix = glm::translate(m_TransformMatrix, m_Position);
	RotateAllAngles(m_TransformMatrix);
	m_TransformMatrix = glm::scale(m_TransformMatrix, m_Scale);
	return m_TransformMatrix;
}

void Rius::Transform::Rotate(float angle, glm::vec3 rotationAngle)
{
	m_XAngle = angle * rotationAngle[0];
	m_YAngle = angle * rotationAngle[1];
	m_ZAngle = angle * rotationAngle[2];

}

void Rius::Transform::Scale(glm::vec3 scale)
{
	m_Scale += scale;
}

void Rius::Transform::RotateAllAngles(glm::mat4& trans) const
{
	trans = glm::rotate(trans, m_XAngle, glm::vec3(1, 0, 0));
	trans = glm::rotate(trans, m_YAngle, glm::vec3(0, 1, 0));
	trans = glm::rotate(trans, m_ZAngle, glm::vec3(0, 0, 1));
}

//
//void Rius::Transform::SetRotation(glm::vec3& rotation)
//{
//	m_Rotation = rotation;
//}
//
//void Rius::Transform::SetRotation(float x, float y, float z)
//{
//}

#include "MiniginPCH.h"
#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>

#include "CircleCollider3D.h"
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

Rius::Transform::Transform(const Transform& other)
{
	this->m_pGameObject = other.m_pGameObject;
	this->m_Position = other.m_Position;
	this->m_Scale = other.m_Scale;
	this->m_ZAngle = other.m_ZAngle;
	this->m_TransformMatrix = other.m_TransformMatrix;
	this->m_TransformedPos = other.m_TransformedPos;
	this->m_YAngle = other.m_YAngle;
	this->m_XAngle = other.m_XAngle;
}

Rius::BaseComponent* Rius::Transform::Clone()
{
	return new Transform{ *this };
}

void Rius::Transform::SetComponent(BaseComponent* comp)
{
	Transform* component = static_cast<Transform*>(comp);
	this->m_pGameObject = component->m_pGameObject;
	this->m_Position = component->m_Position;
	this->m_Scale = component->m_Scale;
	this->m_ZAngle = component->m_ZAngle;
	this->m_TransformMatrix = component->m_TransformMatrix;
	this->m_TransformedPos = component->m_TransformedPos;
	this->m_YAngle = component->m_YAngle;
	this->m_XAngle = component->m_XAngle;
}

void Rius::Transform::Initialize()
{
}

void Rius::Transform::Update(float )
{
}

void Rius::Transform::Render() const
{
}

glm::vec3 Rius::Transform::GetPosition() const
{
	glm::vec3 newPos = glm::vec3(m_Position);
	return newPos;
}

glm::vec3 Rius::Transform::GetScale() const
{
	return m_Scale;
}

void Rius::Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = -y;
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

void Rius::Transform::Translate(const glm::vec3& newPos)
{

	m_Position.x += newPos.x;
	m_Position.y += -newPos.y;
	m_Position.z += newPos.z;
}

void Rius::Transform::Rotate(float angle, glm::vec3 rotationAngle)
{
	m_XAngle = angle * rotationAngle[0];
	m_YAngle = angle * rotationAngle[1];
	m_ZAngle = angle * rotationAngle[2];

}

void Rius::Transform::Scale(glm::vec3 scale)
{
	m_Scale = scale;
}

void Rius::Transform::RotateAllAngles(glm::mat4& trans) const
{
	trans = glm::rotate(trans, m_XAngle, glm::vec3(1, 0, 0));
	trans = glm::rotate(trans, m_YAngle, glm::vec3(0, 1, 0));
	trans = glm::rotate(trans, m_ZAngle, glm::vec3(0, 0, 1));
}
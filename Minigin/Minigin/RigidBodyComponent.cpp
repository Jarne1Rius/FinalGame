#include "MiniginPCH.h"
#include "RigidBodyComponent.h"
#include "GameObject.h"
#include "Minigin.h"
#include "time.h"
#include <glm/gtx/norm.hpp>
Rius::RigidBodyComponent::RigidBodyComponent(float mass)
	:m_AccelerationForce(0, 9.81f), m_Velocity(0, 0, 0), m_Mass(mass), m_Kinematic(), m_MaxForce(0.5f)
{
}

Rius::RigidBodyComponent::~RigidBodyComponent()
{
}

Rius::RigidBodyComponent::RigidBodyComponent(const RigidBodyComponent& other)
{
	m_Velocity = other.m_Velocity;
	m_Kinematic = other.m_Kinematic;
	m_AccelerationForce = other.m_AccelerationForce;
	m_Mass = other.m_Mass;
	m_pGameObject = other.m_pGameObject;
}


void Rius::RigidBodyComponent::SetComponent(BaseComponent* comp)
{
	RigidBodyComponent* component = static_cast<RigidBodyComponent*>(comp);
	this->m_Velocity = component->m_Velocity;
	this->m_Kinematic = component->m_Kinematic;
	this->m_AccelerationForce = component->m_AccelerationForce;
	this->m_Mass = component->m_Mass;
	this->m_pGameObject = component->m_pGameObject;
}

void Rius::RigidBodyComponent::AddForce(glm::vec2 force)
{

	m_Velocity.x += force.x;
	m_Velocity.y -= force.y;
	if (glm::length2(m_Velocity) > (m_MaxForce * m_MaxForce))
	{
		m_Velocity = glm::normalize(m_Velocity) * m_MaxForce;
	}
}

void Rius::RigidBodyComponent::Bounce(float multiply)
{
	//if (!m_OnGround)
	//{
	glm::vec2 previous = m_Velocity;
	m_Velocity *= 0;

	if (previous.y < 0 && abs(m_Velocity.y) < 0.001f)
	{
		m_OnGround = true;
		m_Velocity.y = 0;
	}
	m_pGameObject->GetTransform().SetPosition(m_pGameObject->m_PreviousPos);
	//}
	//else
	//	m_pGameObject->GetTransform().SetPosition(m_pGameObject->m_PreviousPos);
}

void Rius::RigidBodyComponent::Initialize()
{
}

void Rius::RigidBodyComponent::Update()
{
	if (abs(m_Velocity.y) > 0.01f)
	{
		m_OnGround = false;
	}
	if (!m_UpdatePos)
		m_pGameObject->m_PreviousPos = m_pGameObject->GetTransform().GetPosition();
	else
		m_UpdatePos = false;
	Transform& transform = m_pGameObject->GetTransform();
	if (!m_Kinematic)
		m_Velocity += ((glm::vec3(m_AccelerationForce, 0) * m_Mass) / 100000.f);
	transform.SetPosition(transform.GetPosition() + m_Velocity * Time::m_DeltaTime);
}

void Rius::RigidBodyComponent::Render() const
{
}

void Rius::RigidBodyComponent::SetKinematic(bool kinematic)
{
	m_Kinematic = kinematic;
	Minigin::m_UndoSystem.AddAction(this);
}

bool Rius::RigidBodyComponent::IsOnGround()
{
	return m_OnGround;
}

void Rius::RigidBodyComponent::MoveTo(const glm::vec3& location)
{
	//m_Prev = GetGameObject()->GetTransform().GetPosition();
	m_Velocity.x = glm::vec3{ location - GetGameObject()->GetTransform().GetPosition() }.x;
	m_UpdatePos = true;
	m_pGameObject->m_PreviousPos = m_pGameObject->GetTransform().GetPosition();
	GetGameObject()->GetTransform().SetPosition(location);

}

Rius::BaseComponent* Rius::RigidBodyComponent::Clone()
{
	return new RigidBodyComponent{ *this };
}


#include "MiniginPCH.h"
#include "RigidBodyComponent.h"
#include "GameObject.h"
#include "Minigin.h"
#include "time.h"
#include <glm/gtx/norm.hpp>

#include "Logger.h"

Rius::RigidBodyComponent::RigidBodyComponent(float mass)
	:m_AccelerationForce(0, 9.81f), m_Velocity(0, 0, 0), m_Mass(mass), m_Kinematic(false), m_MaxForce(2.f)
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

	m_Velocity.x += force.x * 10;
	m_Velocity.y -= force.y * 10;
	if (glm::length2(m_Velocity) > (m_MaxForce * m_MaxForce))
	{
		//m_Velocity = glm::normalize(m_Velocity) * m_MaxForce;
	}
}

void Rius::RigidBodyComponent::Bounce(float multiply)
{
	if (!m_OnGround)
	{
		glm::vec2 previous = m_Velocity;

		if (abs(m_Velocity.x) == 0)
		{
			m_Velocity *= m_BounceMulti;

		}
		else
		{
			m_pGameObject->GetTransform().SetPosition(m_pGameObject->GetTransform().GetPosition().x, -m_pGameObject->m_PreviousPos.y, m_pGameObject->GetTransform().GetPosition().z);
			m_Velocity.y *= m_BounceMulti;
		}

		if (previous.y < 0 && abs(m_Velocity.y) < 0.001f)
		{
			m_OnGround = true;
			m_Velocity.y = 0;
		}
		m_pGameObject->GetTransform().SetPosition(m_pGameObject->m_PreviousPos);
	}
	else
	{
		m_pGameObject->GetTransform().SetPosition(m_pGameObject->m_PreviousPos);
	}
}

void Rius::RigidBodyComponent::Initialize()
{
	m_pGameObject->m_PreviousPos = m_pGameObject->GetTransform().GetPosition();
}

void Rius::RigidBodyComponent::Update(float deltaT)
{

	//Logger::LogInfo(glm::vec2{ m_Velocity.x,m_Velocity.y });
	if (abs(m_Velocity.y) > 0.01f && !m_Kinematic)
	{
		m_OnGround = false;
	}
	if (!m_UpdatePos)
		m_pGameObject->m_PreviousPos = m_pGameObject->GetTransform().GetPosition();
	else
		m_UpdatePos = false;
	Transform& transform = m_pGameObject->GetTransform();
	if (!m_Kinematic)
		m_Velocity += ((glm::vec3(m_AccelerationForce, 0) * m_Mass) * 1.f);
	transform.SetPosition(transform.GetPosition() + m_Velocity * deltaT);
}

void Rius::RigidBodyComponent::Render() const
{
}

void Rius::RigidBodyComponent::SetKinematic(bool kinematic)
{
	m_Kinematic = kinematic;
	//Minigin::m_UndoSystem.AddAction(this);
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
	m_pGameObject->m_PreviousPos = m_pGameObject->GetTransform().GetPosition() + glm::vec3{ 0,-0.1f,0 };
	GetGameObject()->GetTransform().SetPosition(location);

}

void Rius::RigidBodyComponent::OnCollisionEnter(Collider* collider)
{
	if (!m_pGameObject->GetStatic() || !m_Kinematic)
		Bounce(1.f);
}

Rius::BaseComponent* Rius::RigidBodyComponent::Clone()
{
	return new RigidBodyComponent{ *this };
}


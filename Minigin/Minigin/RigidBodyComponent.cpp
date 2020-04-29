#include "MiniginPCH.h"
#include "RigidBodyComponent.h"
#include "GameObject.h"
#include "time.h"
Rius::RigidBodyComponent::RigidBodyComponent(float mass)
	:m_AccelerationForce(0, 9.81f), m_Velocity(0, 0), m_Mass(mass)
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

void Rius::RigidBodyComponent::AddForce(glm::vec2& force)
{
	m_Velocity.x += force.x;
	m_Velocity.y -= force.y;
}

void Rius::RigidBodyComponent::Bounce(float multiply)
{
	m_Velocity.y = -m_Velocity.y * multiply;
	m_Velocity.x = m_Velocity.x * multiply;
}

void Rius::RigidBodyComponent::Initialize()
{
}

void Rius::RigidBodyComponent::Update()
{
	Transform& transform = m_pGameObject->GetTransform();
	if (!m_Kinematic)
		m_Velocity += (m_AccelerationForce * m_Mass) / 1000000.f;
	transform.SetPosition(transform.GetPosition() + glm::vec3(m_Velocity * Time::m_DeltaTime, 0));
}

void Rius::RigidBodyComponent::Render() const
{
}

void Rius::RigidBodyComponent::SetKinematic(bool kinematic)
{
	m_Kinematic = kinematic;
}

Rius::BaseComponent* Rius::RigidBodyComponent::Clone()
{
	return new RigidBodyComponent{ *this };
}


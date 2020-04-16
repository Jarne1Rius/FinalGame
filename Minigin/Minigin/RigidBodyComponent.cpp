#include "MiniginPCH.h"
#include "RigidBodyComponent.h"
#include "GameObject.h"
#include "time.h"
Rius::RigidBodyComponent::RigidBodyComponent(float mass)
	:m_AccelerationForce(0,9.81f), m_Velocity(0,0),m_Mass(mass) 
{
}

Rius::RigidBodyComponent::~RigidBodyComponent()
{
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
	m_Velocity += (m_AccelerationForce * m_Mass)/1000000.f;
	transform.SetPosition(transform.GetPosition() + glm::vec3(m_Velocity * Time::m_DeltaTime, 0));
}

void Rius::RigidBodyComponent::Render() const
{
}
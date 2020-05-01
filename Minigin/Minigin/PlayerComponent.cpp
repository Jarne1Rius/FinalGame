#include "MiniginPCH.h"
#include "PlayerComponent.h"

Rius::PlayerComponent::PlayerComponent()
	:m_FSM(),m_MovementSpeed(),m_GamepadID(),m_Lives()
{
}

Rius::PlayerComponent::~PlayerComponent()
{
	delete m_FSM;
}

Rius::PlayerComponent::PlayerComponent(const PlayerComponent& other)
{
	this->m_FSM = other.m_FSM;
	this->m_GamepadID = other.m_GamepadID;
	this->m_Lives = other.m_Lives;
	this->m_MovementSpeed = other.m_MovementSpeed;
	this->m_pGameObject = other.m_pGameObject;
	this->m_Id = other.m_Id;
}

void Rius::PlayerComponent::SetComponent(BaseComponent* comp)
{
	PlayerComponent* component = static_cast<PlayerComponent*>(comp);
	this->m_FSM = component->m_FSM;
	this->m_GamepadID = component->m_GamepadID;
	this->m_Lives = component->m_Lives;
	this->m_MovementSpeed = component->m_MovementSpeed;
	this->m_pGameObject = component->m_pGameObject;
	this->m_Id = component->m_Id;
}

Rius::BaseComponent* Rius::PlayerComponent::Clone()
{
	return new PlayerComponent{ *this };
}

void Rius::PlayerComponent::Initialize()
{
	StateClass* running = new StateClass{};
	StateClass* idle = new StateClass{};
	StateClass* menu = new StateClass{};
	StateClass* jumping = new StateClass{};
	StateClass* attack = new StateClass{};
	StateClass* defeat = new StateClass{};
	int a{};
	auto isDeadLambda = [this]()->bool {if (m_Lives <= 3)std::cout << "Test\n"; return this->m_Lives <= 3; };
	Transition* IsDead = new Transition{ isDeadLambda,running,defeat };
	IsDead = new Transition{ isDeadLambda,idle,defeat };
	IsDead = new Transition{ isDeadLambda,jumping,defeat };
	IsDead = new Transition{ isDeadLambda,attack,defeat };
	m_FSM = new FiniteStateMachine{ {running,idle,menu,jumping,attack,defeat} };
	m_FSM->m_CurrentState = idle;
}

void Rius::PlayerComponent::Update()
{
	m_FSM->UpdateState();
}

void Rius::PlayerComponent::Render() const
{
}

void Rius::PlayerComponent::TakeDamage()
{
}


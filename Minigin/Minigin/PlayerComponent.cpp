#include "MiniginPCH.h"
#include "PlayerComponent.h"
#include "InputManager.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "SceneManager.h"
#include "Scene.h"
Rius::PlayerComponent::PlayerComponent(int idInput, GameObject* prefabBullets)
	:m_FSM(), m_MovementSpeed(), m_GamepadID(), m_Lives(3), m_IdInput(idInput), m_Moving(1.f), m_Jump(), m_Sprite(), m_Attack(), m_Rigid(), m_BulletsPrefabs(prefabBullets)
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
	State* running = new State{ "running" };
	State* idle = new State{ "idle" };
	State* menu = new State{ "menu" };
	State* jumping = new State{ "jumping" };
	State* attack = new State{ "attack" };
	State* defeat = new State{ "defeat" };

	auto isDeadLambda = [this]()->bool
	{
		return this->m_Lives <= 0;
	};
	auto jump = [this]()->bool
	{
		if (m_Jump && this->m_Rigid->IsOnGround()) {
			m_Jump = false;
			m_Rigid->AddForce(glm::vec2{ 0,1.f });
			return true;
		}
		return false;
	};
	auto stopJump = [this]()->bool
	{
		if (this->m_Rigid->IsOnGround()) {
			this->m_Jump = false;
			return true;
		}
		return false;
	};
	auto attacking = [this]()->bool {return m_Attack; };
	auto stopAttacking = [this]()->bool
	{
		return !m_Attack;
	};
	auto moving = [this]()->bool
	{
		if (m_Moving != 0)
			return true;
		return false;
	};
	running->SetTransition(isDeadLambda, defeat);
	running->SetTransition(jump, jumping);
	running->SetTransition(attacking, attack);

	idle->SetTransition(isDeadLambda, defeat);
	idle->SetTransition(jump, jumping);
	idle->SetTransition(attacking, attack);
	idle->SetTransition(moving, running);

	jumping->SetTransition(isDeadLambda, defeat);
	jumping->SetTransition(attacking, attack);
	jumping->SetTransition(stopJump, idle);

	attack->SetTransition(isDeadLambda, defeat);
	attack->SetTransition(stopAttacking, idle);
	attack->SetTransition(jump, jumping);

	m_FSM = new FiniteStateMachine{ {running,idle,menu,jumping,attack,defeat} };
	m_FSM->m_CurrentState = idle;

	auto StartFiring = [this]()->void
	{
	//	SceneManager::GetCurrentScene()->Add(m_BulletsPrefabs[0].Clone());
	};
	m_Rigid = m_pGameObject->GetRigidBodyComponent();
	attack->SetActionStart(StartFiring);
}

void Rius::PlayerComponent::Update(float deltaT)
{
	if (m_Rigid == nullptr) m_Rigid = m_pGameObject->GetRigidBodyComponent();
	m_FSM->UpdateState();
	std::string name = m_FSM->m_CurrentState->GetName();
	if (name == "running" || name == "jumping")
	{
		//	m_Rigid->MoveTo(this->GetGameObject()->GetTransform().GetPosition() + glm::vec3{ 10.f * m_Moving * Time::m_DeltaTime,0,0 });
			//m_Rigid->AddForce(glm::vec2{ 0.001f * m_Moving * Time::m_DeltaTime,0 }); 
	}
}

void Rius::PlayerComponent::Render() const
{
}

void Rius::PlayerComponent::TakeDamage(int amount)
{
	m_Lives -= amount;
}

void Rius::PlayerComponent::Jump(float value)
{
	std::string name = m_FSM->m_CurrentState->GetName();
	if (name != "Menu" || name != "Defeat")
		m_Jump = true;
}

void Rius::PlayerComponent::Move(float value)
{
	m_Moving = value;
}

void Rius::PlayerComponent::Fire(float value)
{
	std::cout << "test\n";
	std::string name = m_FSM->m_CurrentState->GetName();
	if (name != "Menu" || name != "Defeat")
		m_Attack = true;
}

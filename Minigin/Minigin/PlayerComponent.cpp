#include "MiniginPCH.h"
#include "PlayerComponent.h"

#include "BoxCollider2D.h"
#include "BulletPrefab.h"
#include "InputManager.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "SceneManager.h"
#include "Scene.h"
Rius::PlayerComponent::PlayerComponent(GameObject* prefabBullets)
	:m_FSM(), m_MovementSpeed(), m_Lives(3), m_Moving(1.f), m_Jump(), m_Sprite(), m_Attack(), m_Rigid(), m_BulletsPrefabs(prefabBullets),m_pCollider()
{
}

Rius::PlayerComponent::~PlayerComponent()
{
//	delete m_BulletsPrefabs;
	delete m_FSM;
}

Rius::PlayerComponent::PlayerComponent(const PlayerComponent& other)
	:m_pCollider(other.m_pCollider),
	m_FSM(),
	m_Lives(),
	m_Jump(),
	m_Attack(),
	m_Sprite(),
	m_Moving(),
	m_BulletsPrefabs(), m_MovementSpeed(), m_Rigid()
{
	this->m_FSM = other.m_FSM;
	this->m_Lives = other.m_Lives;
	this->m_MovementSpeed = other.m_MovementSpeed;
	this->m_pGameObject = other.m_pGameObject;
	this->m_Id = other.m_Id;
}

void Rius::PlayerComponent::SetComponent(BaseComponent* comp)
{
	PlayerComponent* component = static_cast<PlayerComponent*>(comp);
	this->m_FSM = component->m_FSM;
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
	auto ableToJump = [this]()->bool
	{
		return (m_Jump && this->m_Rigid->IsOnGround());
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
		m_Attack = false;
		return m_Sprite->CheckOneCicle();
	};
	auto moving = [this]()->bool
	{
		if (m_Moving != 0)
			return true;
		return false;
	};
	auto stopMoving = [this]()->bool {return m_Moving == 0; };
	running->AddTransition(isDeadLambda, defeat);
	running->AddTransition(ableToJump, jumping);
	running->AddTransition(attacking, attack);
	running->AddTransition(stopMoving, idle);

	idle->AddTransition(isDeadLambda, defeat);
	idle->AddTransition(ableToJump, jumping);
	idle->AddTransition(attacking, attack);
	idle->AddTransition(moving, running);

	jumping->AddTransition(isDeadLambda, defeat);
	jumping->AddTransition(attacking, attack);
	jumping->AddTransition(stopJump, idle);

	attack->AddTransition(isDeadLambda, defeat);
	attack->AddTransition(stopAttacking, idle);
	attack->AddTransition(ableToJump, jumping);

	m_FSM = new FiniteStateMachine{ {running,idle,menu,jumping,attack,defeat} };
	m_FSM->m_CurrentState = idle;

	auto checkCollisionWhileGoingUp = [this]()->void
	{
		if (m_Rigid->GetVelocity().y < 0 && !m_Rigid->IsOnGround())m_pCollider->SwitchToTrigger(true);
		else m_pCollider->SwitchToTrigger(false);
	};
	auto StartFiring = [this]()->void
	{
		BulletPrefab* bullet = static_cast<BulletPrefab*>(m_BulletsPrefabs[0].Clone());
		bullet->GetTransform().SetPosition((m_pGameObject->GetTransform().GetScale().x > 0) ? m_pGameObject->GetTransform().GetPosition() : m_pGameObject->GetTransform().GetPosition() + glm::vec3{ -50,0,0 });
		SceneManager::GetCurrentScene()->Add(bullet);
		bullet->GetRigidBodyComponent()->AddForce({ (m_pGameObject->GetTransform().GetScale().x > 0) ? 10.f : -10.f,0 });
	};

	auto startOfRunning = [this]()->void {m_Sprite->SetAnimation("Running"); };
	auto startOfIdle = [this]()->void {m_Sprite->SetAnimation("Idle"); };
	auto startOfAttack = [this]()->void {m_Sprite->SetAnimation("Attack"); };
	auto startJumping = [this]()->void
	{
		m_Jump = false;
		m_Rigid->ResetUp();
		m_Rigid->AddForce(glm::vec2{ 0,30.f });
	};

	jumping->AddActionStart(startJumping);
	attack->AddActionStart(StartFiring);
	attack->AddActionStart(startOfAttack);
	running->AddActionStart(startOfRunning);
	idle->AddActionStart(startOfIdle);
	jumping->AddActionStart(startOfIdle);

	m_Sprite = m_pGameObject->GetComponent<SpriteSheetComponent>();
	m_FSM->AddActionTo(checkCollisionWhileGoingUp, { jumping ,attack, idle });
	m_pCollider = m_pGameObject->GetComponent<BoxCollider2D>();
	m_Rigid = m_pGameObject->GetRigidBodyComponent();

	m_pGameObject->Notify(this->m_pGameObject, Event::AddPlayer);
}

void Rius::PlayerComponent::Update(float deltaT)
{
	if (m_Rigid == nullptr) m_Rigid = m_pGameObject->GetRigidBodyComponent();
	m_FSM->UpdateState();
	std::string name = m_FSM->m_CurrentState->GetName();
	if (name == "running" || name == "jumping" || name == "idle")
	{
		if (m_Moving < 0) m_pGameObject->GetTransform().Scale({ -1,1 ,1 });
		else if (m_Moving > 0) m_pGameObject->GetTransform().Scale({ 1,1 ,1 });
		m_Rigid->MoveTo(this->GetGameObject()->GetTransform().GetPosition() + glm::vec3{ 150.f * m_Moving * deltaT,0,0 });
	}
}

void Rius::PlayerComponent::Render() const
{
}

void Rius::PlayerComponent::TakeDamage(int amount)
{
	m_Lives -= amount;
}

void Rius::PlayerComponent::Jump(float)
{
	std::string name = m_FSM->m_CurrentState->GetName();
	if (name != "Menu" || name != "Defeat" || name != "Attack")
		m_Jump = true;
}

void Rius::PlayerComponent::Move(float value)
{
	//std::cout << value << "\n";
	m_Moving = value;
}

void Rius::PlayerComponent::Fire(float)
{
	std::string name = m_FSM->m_CurrentState->GetName();
	if (name != "Menu" || name != "Defeat")
		m_Attack = true;
}

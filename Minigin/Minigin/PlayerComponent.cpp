#include "MiniginPCH.h"
#include "PlayerComponent.h"

#include "BoxCollider2D.h"
#include "BulletPrefab.h"
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
	delete m_BulletsPrefabs;
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
	running->SetTransition(isDeadLambda, defeat);
	running->SetTransition(ableToJump, jumping);
	running->SetTransition(attacking, attack);
	running->SetTransition(stopMoving, idle);

	idle->SetTransition(isDeadLambda, defeat);
	idle->SetTransition(ableToJump, jumping);
	idle->SetTransition(attacking, attack);
	idle->SetTransition(moving, running);

	jumping->SetTransition(isDeadLambda, defeat);
	jumping->SetTransition(attacking, attack);
	jumping->SetTransition(stopJump, idle);

	attack->SetTransition(isDeadLambda, defeat);
	attack->SetTransition(stopAttacking, idle);
	attack->SetTransition(ableToJump, jumping);

	m_FSM = new FiniteStateMachine{ {running,idle,menu,jumping,attack,defeat} };
	m_FSM->m_CurrentState = idle;

	auto checkCollisionWhileGoingUp = [this]()->void
	{
		if (m_Rigid->GetVelocity().y < 0 && !m_Rigid->IsOnGround())m_pCollider->SetIgnoreGroups(Group0, true);
		else m_pCollider->SetIgnoreGroups(Group0, false);
	};
	auto StartFiring = [this]()->void
	{
		BulletPrefab* bullet = static_cast<BulletPrefab*>(m_BulletsPrefabs[0].Clone());
		bullet->GetTransform().SetPosition((m_pGameObject->GetTransform().GetScale().x > 0) ? m_pGameObject->GetTransform().GetPosition() : m_pGameObject->GetTransform().GetPosition() + glm::vec3{ -50,0,0 });
		SceneManager::GetCurrentScene()->Add(bullet);
		bullet->GetRigidBodyComponent()->AddForce({ (m_pGameObject->GetTransform().GetScale().x > 0) ? 0.1f : -0.1f,0 });
		//bullet->GetTransform().Scale({ -1,-1,-1 });
	};

	auto startOfRunning = [this]()->void {m_Sprite->SetAnimation("Running"); };
	auto startOfIdle = [this]()->void {m_Sprite->SetAnimation("Idle"); };
	auto startOfAttack = [this]()->void {m_Sprite->SetAnimation("Attack"); };
	auto startJumping = [this]()->void
	{
		m_Jump = false;
		m_Rigid->ResetUp();
		m_Rigid->AddForce(glm::vec2{ 0,2.f });
	};

	jumping->SetActionStart(startJumping);
	attack->SetActionStart(StartFiring);
	attack->SetActionStart(startOfAttack);
	running->SetActionStart(startOfRunning);
	idle->SetActionStart(startOfIdle);
	jumping->SetActionStart(startOfIdle);

	m_Sprite = m_pGameObject->GetComponent<SpriteSheetComponent>();
	m_FSM->AddActionTo(checkCollisionWhileGoingUp, { jumping ,attack});
	m_pCollider = m_pGameObject->GetComponent<BoxCollider2D>();
	m_Rigid = m_pGameObject->GetRigidBodyComponent();
}

void Rius::PlayerComponent::Update(float deltaT)
{
	if (m_Rigid == nullptr) m_Rigid = m_pGameObject->GetRigidBodyComponent();
	m_FSM->UpdateState();
	std::string name = m_FSM->m_CurrentState->GetName();
	if (name == "running" || name == "jumping")
	{
		if (m_Moving < 0) m_pGameObject->GetTransform().Scale({ -1,1 ,1 });
		else if (m_Moving > 0) m_pGameObject->GetTransform().Scale({ 1,1 ,1 });
		m_Rigid->MoveTo(this->GetGameObject()->GetTransform().GetPosition() + glm::vec3{ 0.1f * m_Moving * deltaT,0,0 });
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
	if (name != "Menu" || name != "Defeat" || name != "Attack")
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

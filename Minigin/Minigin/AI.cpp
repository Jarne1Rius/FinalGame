#include "MiniginPCH.h"
#include "AI.h"
#include "GameObject.h"
#include "RigidBodyComponent.h"
#include "Time.h"
#include <glm/gtc/random.hpp>
#include "BoxCollider2D.h"
#include "Logger.h"
#include "MaterialManager.h"
#include "SceneManager.h"
#include "SpriteSheetComponent.h"
#include "UI.h"
#include "Scene.h"
#include "TextureMaterial.h"

Rius::Ai::Ai(float durationWalking, const glm::vec2& randomRangeWalking, bool target)
	:m_Sec(), m_SecWalking(durationWalking), m_Radius(), m_RandomRangeWalking(randomRangeWalking), m_Rigid(), m_pFSM(), m_CurrentTarget(), m_Value(100)
,m_Lives(1),m_pCollider(),m_HitPlayer(),m_Targets(),m_DurationRunning(),m_Direction(),m_TypeChase(),m_Animation(),m_StartFollowing()
{

}

Rius::Ai::~Ai()
{
	delete m_pFSM;
}

void Rius::Ai::Initialize()
{
	m_Rigid = m_pGameObject->GetRigidBodyComponent();
	State* follow = new State{ "Follow" };
	State* wander = new State{ "Wander" };
	State* jumping = new State{ "jumping" };
	State* WalkingL = new State{ "WalkingL" };
	State* WalkingR = new State{ "WalkingR" };
	State* death = new State{ "Death" };
	State* idle = new State{ "Idle" };
	State* hitPlayer = new State{ "HitPlayer" };
	State* AfterDeath = new State{ "AfterDeath" };
	m_pFSM = new FiniteStateMachine{ {follow, wander, death, idle,jumping,WalkingL,WalkingR, AfterDeath,hitPlayer} };
	m_pFSM->m_CurrentState = wander;
	auto toWander = [this]()->bool
	{
		return m_CurrentTarget == nullptr;
	};
	auto startGame = [this]()->bool
	{
		return false;
	};
	auto startFollowing = [this]()->bool
	{
		return m_CurrentTarget != nullptr;
	};
	auto isDead = [this]()->bool
	{
		return m_Lives <= 0;
	};
	auto walkToLeft = [this]()->bool
	{
		return m_Sec > glm::linearRand(m_RandomRangeWalking.x, m_RandomRangeWalking.y) && m_Rigid->IsOnGround();
	};
	auto tryToJump = [this]()->bool
	{
		return m_Sec > glm::linearRand(m_RandomRangeWalking.x, m_RandomRangeWalking.y);
	};
	auto StopJumping = [this]()->bool
	{
		//check this possible that it doesn't work
		return m_Rigid->IsOnGround();
	};
	auto StopWalking = [this]()->bool
	{
		return m_Sec < 0;
	};
	auto transformToFood = [this]()->bool
	{
		return (m_Sec > 3);
	};
	auto toHitplayer = [this]()->bool {return m_HitPlayer; };
	auto stopHitplayer = [this]()->bool {return m_Sec > 0; };

	wander->AddTransition(startFollowing, follow);
	idle->AddTransition(startFollowing, follow);
	follow->AddTransition(toWander, wander);
	idle->AddTransition(toWander, wander);
	wander->AddTransition(walkToLeft, WalkingL);
	wander->AddTransition(walkToLeft, WalkingR);
	wander->AddTransition(tryToJump, jumping);
	WalkingL->AddTransition(StopWalking, wander);
	WalkingR->AddTransition(StopWalking, wander);
	jumping->AddTransition(StopJumping, wander);
	death->AddTransition(transformToFood, AfterDeath);

	m_pFSM->AddTransitionsTo(isDead, { wander,WalkingR,WalkingL,jumping, follow }, death);
	m_pFSM->AddTransitionsTo(toHitplayer, { wander,WalkingR,WalkingL,jumping, follow }, hitPlayer);
	hitPlayer->AddTransition(stopHitplayer, wander);

	//Actions
	auto UpdateSecLeftDuraion = [this]()->void
	{
		m_pGameObject->GetTransform().Scale({ -1, 1, 1 });
		m_Sec -= (Time::m_DeltaTime / 2.f);
		//m_Rigid->MoveTo(m_pGameObject->GetTransform().GetPosition() + glm::vec3{ -0.1f,0,0 });
		m_Rigid->AddForce(glm::vec2{ -20.2f * Time::m_DeltaTime,0.f });
	};
	auto UpdateSecRightDuraion = [this]()->void
	{
		m_pGameObject->GetTransform().Scale({ 1, 1, 1 });
		m_Sec -= Time::m_DeltaTime / 2.f;
		//m_Rigid->MoveTo(m_pGameObject->GetTransform().GetPosition() + glm::vec3{ 0.1f,0,0 });
		m_Rigid->AddForce(glm::vec2{ 20.2f * Time::m_DeltaTime,0.f });
		//update to left
	};
	auto UpdateSecWanderDuraion = [this]()->void
	{
		m_Rigid->SetForce({0, m_Rigid->GetVelocity().y, 0});
		m_Sec += Time::m_DeltaTime;
		//std::cout << "wander\n";
		//update to left
	};
	auto StartWalking = [this]()->void
	{
		m_Animation->SetAnimation("Running");
		m_Sec = m_SecWalking;
	};
	auto Jump = [this]()->void
	{
		m_Rigid->AddForce(glm::vec2{ 0,30.6f });
		m_Sec = 0;
	};
	auto justDied = [this]()->void
	{
		m_Animation->SetAnimation("Death");
		m_Sec = 0;
		//m_pCollider
		bool t[4] = { true, true, true, false };
		m_pCollider->SetIgnoreGroups(t);
		m_Rigid->SetBounceMulti(1);
		m_Rigid->SetKinematic(true);
		m_Rigid->AddForce(glm::vec2{ glm::linearRand(10,10) * glm::linearRand(-1,1), glm::linearRand(10,10) * glm::linearRand(-1,1) });
	};
	auto updateDeath = [this]()->void
	{
		m_Sec += Time::m_DeltaTime;
	};
	auto transformSpriteToFood = [this]()->void
	{
		bool t[4] = { false, false, false, false };
		m_pCollider->SetIgnoreGroups(t);
		m_Rigid->SetForce({ 0,0,0 });
		m_Rigid->SetKinematic(false);
		m_Rigid->SetBounceMulti(0);
		SpriteSheetComponent* sprite = m_pGameObject->GetComponent<SpriteSheetComponent>();
		sprite->SetAnimation("Food");
		sprite->SetFrame(2);
	};
	auto whileJumping = [this]()->void
	{
		if (m_Rigid->GetVelocity().y < 0 && !m_Rigid->IsOnGround())m_pCollider->SwitchToTrigger(true);
		else m_pCollider->SwitchToTrigger(false);
	};
	auto startIdle = [this]()->void {m_Animation->SetAnimation("Idle"); };
	auto startHit = [this]()->void
	{
		m_Sec = -2;
	};
	auto endHit = [this]()->void {m_HitPlayer = false; };
	hitPlayer->AddActionStart(startHit);
	hitPlayer->AddActionEnd(endHit);
	hitPlayer->AddAction(updateDeath);
	jumping->AddAction(whileJumping);
	jumping->AddActionStart(Jump);
	WalkingL->AddAction(UpdateSecLeftDuraion);
	WalkingR->AddAction(UpdateSecRightDuraion);
	wander->AddAction(UpdateSecWanderDuraion);
	wander->AddActionStart(startIdle);
	WalkingL->AddActionStart(StartWalking);
	WalkingR->AddActionStart(StartWalking);
	death->AddActionStart(justDied);
	death->AddAction(updateDeath);
	AfterDeath->AddActionStart(transformSpriteToFood);
	//Collider check
	m_pCollider = m_pGameObject->GetComponent<BoxCollider2D>();
	if (m_pCollider == nullptr)
	{
		Logger::LogError("No Collider detected");
		assert(m_pCollider != nullptr);
	}
	m_Animation = m_pGameObject->GetComponent<SpriteSheetComponent>();

	m_pGameObject->Notify(this->m_pGameObject, Event::AddEnemy);
}

void Rius::Ai::Render() const
{
}

void Rius::Ai::Update(float deltaT)
{
}

void Rius::Ai::LateUpdate()
{
	m_pFSM->UpdateState();
	GameObject* closest = nullptr;
	float minDistance = FLT_MAX;


}

void Rius::Ai::SetCurrentTarget(GameObject* currentTarget)
{
	auto it = std::find(m_Targets.begin(), m_Targets.end(), currentTarget);
	if (it == m_Targets.end())
	{
		m_Targets.push_back(currentTarget);
	}
	else
	{
		m_CurrentTarget = currentTarget;
	}
}

void Rius::Ai::OnCollisionEnter(Collider* collider)
{
	std::string name = m_pFSM->m_CurrentState->GetName();
	if (name == "AfterDeath" && collider->GetGameObject()->GetTag() == Tag::Player)
	{
		m_pGameObject->Notify(collider->GetGameObject(), Event::addscore);
		m_pGameObject->Notify(this->m_pGameObject, Event::RemoveEnemy);
		SceneManager::GetCurrentScene()->Remove(this->m_pGameObject);
	}
	else if (name != "AfterDeath" && name != "HitPlayer" && collider->GetGameObject()->GetTag() == Tag::Player && !m_HitPlayer)
	{
		m_HitPlayer = true;
		m_pGameObject->Notify(collider->GetGameObject(), Event::hit);

	}
}

void Rius::Ai::OnTriggerEnter(Collider* collider)
{
	std::string name = m_pFSM->m_CurrentState->GetName();
	if(name != "AfterDeath" && collider->GetGameObject()->GetTag() == Tag::Interactions)
	{
		m_Lives--;
	}
	else if (name == "AfterDeath" && collider->GetGameObject()->GetTag() == Tag::Player)
	{
		m_pGameObject->Notify(collider->GetGameObject(), Event::addscore);
		m_pGameObject->Notify(this->m_pGameObject, Event::RemoveEnemy);
		SceneManager::GetCurrentScene()->Remove(this->m_pGameObject);
	}
}
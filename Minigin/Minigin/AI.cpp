#include "MiniginPCH.h"
#include "AI.h"
#include "GameObject.h"
#include "RigidBodyComponent.h"
#include "Time.h"
#include <glm/gtc/random.hpp>
#include "BoxCollider2D.h"
#include "Logger.h"
#include "SpriteSheetComponent.h"
#include "UI.h"

Rius::Ai::Ai(float durationWalking, const glm::vec2& randomRangeWalking, bool target)
	:m_Sec(), m_SecWalking(durationWalking), m_Radius(), m_RandomRangeWalking(randomRangeWalking), m_Rigid(), m_pFSM(), m_CurrentTarget(),m_Value(100)
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
	State* AfterDeath = new State{ "AfterDeath" };
	m_pFSM = new FiniteStateMachine{ {follow, wander, death, idle,jumping,WalkingL,WalkingR, AfterDeath} };
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
		//return false;
		return m_Sec > glm::linearRand(2, 5) && m_Rigid->IsOnGround();
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
	wander->SetTransition(startFollowing, follow);
	idle->SetTransition(startFollowing, follow);
	follow->SetTransition(toWander, wander);
	idle->SetTransition(toWander, wander);
	wander->SetTransition(walkToLeft, WalkingL);
	wander->SetTransition(walkToLeft, WalkingR);
	wander->SetTransition(tryToJump, jumping);
	WalkingL->SetTransition(StopWalking, wander);
	WalkingR->SetTransition(StopWalking, wander);
	jumping->SetTransition(StopJumping, wander);
	death->SetTransition(transformToFood, AfterDeath);

	m_pFSM->AddTransitionsTo(isDead, { wander,WalkingR,WalkingL,jumping, follow }, death);

	//Actions
	auto UpdateSecLeftDuraion = [this]()->void
	{
		m_Sec -= (Time::m_DeltaTime);
		m_Rigid->MoveTo(m_pGameObject->GetTransform().GetPosition() + glm::vec3{ -0.2f,0,0 });
	};
	auto UpdateSecRightDuraion = [this]()->void
	{
		m_Sec -= Time::m_DeltaTime;
		m_Rigid->MoveTo(m_pGameObject->GetTransform().GetPosition() + glm::vec3{ 0.2f,0,0 });
		//m_Rigid->AddForce(glm::vec2{ 0.2f * Time::m_DeltaTime,0.f });
		//update to left
	};
	auto UpdateSecWanderDuraion = [this]()->void
	{
		m_Sec += Time::m_DeltaTime;
		//std::cout << "wander\n";
		//update to left
	};
	auto StartWalking = [this]()->void
	{
		m_Sec = m_SecWalking;
	};
	auto Jump = [this]()->void
	{
		m_Lives = 0;
		//m_Rigid->AddForce(glm::vec2{ 0,1.f });
		m_Sec = 0;
	};
	auto justDied = [this]()->void
	{
		m_Sec = 0;
		//m_pCollider
		bool t[4] = { true, true, true, false };
 		m_pCollider->SetIgnoreGroups(t);
		m_Rigid->SetBounceMulti(1);
		m_Rigid->SetKinematic(true);
		m_Rigid->AddForce(glm::vec2{1,1 });//glm::linearRand(3,5), glm::linearRand(3,5) });
	};
	auto updateDeath = [this]()->void
	{
		m_Sec += Time::m_DeltaTime;
	};
	auto transformSpriteToFood = [this]()->void
	{

		//TODO change this spriteSheetcom
		//m_pGameObject->GetComponent<SpriteSheetComponent>()
	};
	
	jumping->SetActionStart(Jump);
	WalkingL->SetAction(UpdateSecLeftDuraion);
	WalkingR->SetAction(UpdateSecRightDuraion);
	wander->SetAction(UpdateSecWanderDuraion);
	WalkingL->SetActionStart(StartWalking);
	WalkingR->SetActionStart(StartWalking);
	death->SetActionStart(justDied);
	death->SetAction(updateDeath);
	//Collider check
	m_pCollider = m_pGameObject->GetComponent<BoxCollider2D>();
	if (m_pCollider == nullptr)
	{
		Logger::LogError("No Collider detected");
		assert(m_pCollider != nullptr);
	}
}

void Rius::Ai::Render() const
{
}

void Rius::Ai::Update()
{
}

void Rius::Ai::LateUpdate()
{
	m_pFSM->UpdateState();
	GameObject* closest = nullptr;
	float minDistance = FLT_MAX;
	//switch (m_TypeChase)
	//{
	//case ChaseEnemyType::closest:
	//	for (GameObject* target : m_Targets)
	//	{
	//		float distance = glm::distance(target->GetTransform().GetPosition(), GetGameObject()->GetTransform().GetPosition());
	//		if (distance < minDistance)
	//		{
	//			minDistance = distance;
	//			closest = target;
	//		}
	//	}
	//	break;
	//case ChaseEnemyType::furthest:
	//	for (GameObject* target : m_Targets)
	//	{
	//		float distance = glm::distance(target->GetTransform().GetPosition(), GetGameObject()->GetTransform().GetPosition());
	//		if (distance > minDistance)
	//		{
	//			minDistance = distance;
	//			closest = target;
	//		}
	//	}
	//	break;
	//default:;
	//}
	//if (closest != nullptr)
	//{
	//	m_CurrentTarget = closest;
	//}

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
	if(m_pFSM->m_CurrentState->GetName() == "AfterDeath" && collider->GetGameObject()->GetTag() == Tag::Player)
	{
		UI::GetInstance().GetPlayer(collider->GetGameObject()).score += m_Value;
	}
}

void Rius::Ai::OnTriggerEnter(Collider* collider)
{
}
#include "MiniginPCH.h"
#include "AI.h"
#include "GameObject.h"
#include "RigidBodyComponent.h"
#include "Time.h"
#include <glm/gtc/random.hpp>
Rius::Ai::Ai()
{
}

Rius::Ai::~Ai()
{
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
	m_pFSM = new FiniteStateMachine{ {follow, wander, death, idle,jumping,WalkingL,WalkingR} };
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
		return m_Lives < 0;
	};
	auto walkToLeft = [this]()->bool
	{
		return true;
		//return m_Sec > glm::linearRand(2, 5);
	};
	auto tryToJump = [this]()->bool
	{
		return m_Sec > glm::linearRand(2, 4);
	};
	auto StopJumping = [this]()->bool
	{
		//check this possible that it doesn't work
		return m_Rigid->IsOnGround();
	};
	auto StopWalking = [this]()->bool
	{
		;
		return m_Sec < 0;
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
	
	m_pFSM->AddTransitionsTo(isDead, { wander,WalkingR,WalkingL,jumping, follow },death);

	//Actions
	auto UpdateSecLeftDuraion = [this]()->void
	{
		m_Sec -= Time::m_DeltaTime;
		//std::cout << "Left\n";
		m_Rigid->MoveTo(m_pGameObject->GetTransform().GetPosition() + glm::vec3{-0.2f,0,0});
		//m_Rigid->AddForce(glm::vec2{ -0.2f * Time::m_DeltaTime,0.f });
		//update to left
	};
	auto UpdateSecRightDuraion = [this]()->void
	{
		m_Sec -= Time::m_DeltaTime;
		m_Rigid->AddForce(glm::vec2{ 0.2f * Time::m_DeltaTime,0.f });
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
		m_Sec = 0;
	};
	auto Jump = [this]()->void
	{
		std::cout << "jump\n";
		m_Rigid->AddForce(glm::vec2{ 0,1.f });
	};
	jumping->SetActionStart(Jump);
	WalkingL->SetAction(UpdateSecLeftDuraion);
	WalkingR->SetAction(UpdateSecRightDuraion);
	wander->SetAction(UpdateSecWanderDuraion);
	wander->SetActionEnd(StartWalking);
	
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
	switch (m_TypeChase)
	{
	case ChaseEnemyType::closest:
		for (GameObject* target : m_Targets)
		{
			float distance = glm::distance(target->GetTransform().GetPosition(), GetGameObject()->GetTransform().GetPosition());
			if (distance < minDistance)
			{
				minDistance = distance;
				closest = target;
			}
		}
		break;
	case ChaseEnemyType::furthest:
		for (GameObject* target : m_Targets)
		{
			float distance = glm::distance(target->GetTransform().GetPosition(), GetGameObject()->GetTransform().GetPosition());
			if (distance > minDistance)
			{
				minDistance = distance;
				closest = target;
			}
		}
		break;
	default:;
	}
	if (closest != nullptr)
	{
		m_CurrentTarget = closest;
	}

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
	GetGameObject()->GetRigidBodyComponent()->Bounce(0);
	if (!GetGameObject()->GetRigidBodyComponent()->IsOnGround())m_Direction *= -1;
}

void Rius::Ai::Wander()
{
	switch (m_Movement)
	{
	case Movement::jumping:
		break;
	case Movement::running:
		m_Sec += Time::m_DeltaTime;
		if (m_Sec < m_DurationRunning)
			break;
	}
}

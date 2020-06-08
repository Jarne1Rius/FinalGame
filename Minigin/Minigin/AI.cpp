#include "MiniginPCH.h"
#include "AI.h"
#include "GameObject.h"
#include "RigidBodyComponent.h"
#include "Time.h"
Rius::Ai::Ai()
{
}

Rius::Ai::~Ai()
{
}

void Rius::Ai::Initialize()
{
	State* follow = new State{ "Follow" };
	State* wander = new State{ "Wander" };
	State* jumping = new State{ "jumping" };
	State* death = new State{ "Death" };
	State* idle = new State{ "Idle" };
	State* running = new State{ "Running" };
	m_pFSM = new FiniteStateMachine{ {follow, wander, death, idle, running} };
	auto following = [this]()->bool
	{
		return m_CurrentTarget != nullptr;
	};
	auto toWander = [this]()->bool
	{
		return m_CurrentTarget == nullptr;
	};
	auto startGame = [this]()->bool
	{
		//this wil change with instance of game, know when start of game
		return false;
	};
	auto startRunning = [this]()->bool
	{
		return m_StartRunning;
	};
	auto stopRunning = [this]()->bool
	{
		return !m_StartRunning;
	};
	auto isDead = [this]()->bool
	{
		return m_Lives < 0;
	};
	//auto wander = [this]()->void
	//{
	//	//return true;
	//};

}

void Rius::Ai::Render() const
{
}

void Rius::Ai::Update()
{
}

void Rius::Ai::LateUpdate()
{
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

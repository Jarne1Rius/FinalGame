#pragma once
#include "BaseComponent.h"
#include <vector>
#include "FiniteStateMachine.h"

namespace Rius
{
	enum ChaseEnemyType
	{
		closest, furthest
	};

	enum Movement
	{
		running, jumping
	};
	class Ai : public BaseComponent
	{
	public:
		Ai();
		~Ai();
		void Initialize() override;
		void Render() const override;
		void Update() override;
		void LateUpdate() override;
		void SetTarget(const std::vector<GameObject*>& targets) { m_Targets = targets; }
		GameObject* GetCurrentTarget() const { return m_CurrentTarget; }
		void SetCurrentTarget(GameObject* currentTarget);
		void OnCollisionEnter(Collider* collider) override;
	private:
		std::vector<GameObject*> m_Targets;
		GameObject* m_CurrentTarget;
		float m_Radius;
		glm::vec3 m_Direction;
		FiniteStateMachine* m_pFSM;
		ChaseEnemyType m_TypeChase;
		float m_DurationRunning;
		bool m_StartRunning;
		int m_Lives;
		float m_Sec;
		Movement m_Movement;

		void Wander();
	};
}


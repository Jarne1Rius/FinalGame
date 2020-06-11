#pragma once
#include "BaseComponent.h"
#include <vector>
#include "FiniteStateMachine.h"
#include "RigidBodyComponent.h"

namespace Rius
{
	enum ChaseEnemyType
	{
		closest, furthest
	};

	class Ai : public BaseComponent
	{
	public:
		Ai(float durationWalking,const glm::vec2& randomRangeWalking, bool target);
		~Ai();
		void Initialize() override;
		void Render() const override;
		void Update() override;
		void LateUpdate() override;
		void SetTarget(const std::vector<GameObject*>& targets) { m_Targets = targets; }
		GameObject* GetCurrentTarget() const { return m_CurrentTarget; }
		void SetCurrentTarget(GameObject* currentTarget);
		void OnCollisionEnter(Collider* collider) override;
		void OnTriggerEnter(Collider* collider) override;
	private:
		Collider* m_pCollider;
		std::vector<GameObject*> m_Targets;
		RigidBodyComponent* m_Rigid;
		GameObject* m_CurrentTarget;
		float m_Radius;
		glm::vec3 m_Direction;
		FiniteStateMachine* m_pFSM;
		ChaseEnemyType m_TypeChase;
		float m_DurationRunning;
		bool m_StartFollowing;
		int m_Lives;
		float m_Sec;
		float m_SecWalking;
		glm::vec2 m_RandomRangeWalking;
		int m_Value;
	};
}


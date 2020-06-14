#pragma once
#include "BaseComponent.h"
#include <vector>
#include "FiniteStateMachine.h"
#include "RigidBodyComponent.h"
#include "SpriteSheetComponent.h"

namespace Rius
{
	enum ChaseEnemyType
	{
		closest, furthest
	};

	class Ai final : public BaseComponent
	{
	public:
		Ai(float durationWalking,const glm::vec2& randomRangeWalking, bool target, int lives);
		~Ai();
		Ai(const Ai& other) = default;
		Ai(Ai&& other) noexcept = default;
		Ai& operator= (const Ai& other) = default;
		Ai& operator= (Ai&& other) = default;

		
		void Initialize() override;
		void Render() const override;
		void Update(float deltaT) override;
		void LateUpdate() override;

		//TODO Chasing
		void SetTarget(const std::vector<GameObject*>& targets) { m_Targets = targets; }
		GameObject* GetCurrentTarget() const { return m_CurrentTarget; }
		void SetCurrentTarget(GameObject* currentTarget);
		void OnCollisionEnter(Collider* collider) override;
		void OnTriggerEnter(Collider* collider) override;
		void TakeDamage() { m_Lives--; }
	private:
		
		bool m_HitPlayer;
		bool m_StartFollowing;

		int m_Lives;
		
		float m_SecWalking;
		float m_DurationRunning;
		float m_Sec;
		//For chasing not implemented right
		float m_Radius;
		ChaseEnemyType m_TypeChase;
		
		glm::vec2 m_RandomRangeWalking;
		
		FiniteStateMachine* m_pFSM;
		
		GameObject* m_CurrentTarget;
		SpriteSheetComponent* m_Animation;
		Collider* m_pCollider;
		RigidBodyComponent* m_Rigid;
		
		std::vector<GameObject*> m_Targets;

		void SetFsm();
	};
}


#pragma once
#include "BaseComponent.h"
#include "FiniteStateMachine.h"
#include "RigidBodyComponent.h"
#include "SpriteSheetComponent.h"
namespace Rius
{
	class SpriteComponent;

	class PlayerComponent :	public BaseComponent
	{
	public:
		PlayerComponent(GameObject* pPrefabBullet);
		~PlayerComponent();
		PlayerComponent(const PlayerComponent& other);
		PlayerComponent(PlayerComponent&& other) noexcept = default;
		PlayerComponent& operator= (const PlayerComponent& other) = default;
		PlayerComponent& operator= (PlayerComponent&& other) = default;
		void SetComponent(BaseComponent * comp) override;
		BaseComponent* Clone() override;
		void Initialize() override;
		void Update(float deltaT) override;
		void Render() const override;
		void TakeDamage(int amount);
		void Jump(float value);
		void Move(float value);
		void Fire(float value);
	//	void LateUpdate() override;
	public:
		RigidBodyComponent* m_Rigid;
		int m_Lives;
		float m_MovementSpeed;
		FiniteStateMachine* m_FSM;
		SpriteSheetComponent* m_Sprite;
		GameObject* m_BulletsPrefabs;
		Collider* m_pCollider;
		bool m_Jump;
		bool m_Attack;
		float m_Moving;
	};

}


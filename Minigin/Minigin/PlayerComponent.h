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
		PlayerComponent(int idInput, std::vector<SpriteComponent*> pPrefabBullet);
		~PlayerComponent();
		PlayerComponent(const PlayerComponent& other);
		PlayerComponent(PlayerComponent&& other) noexcept = default;
		PlayerComponent& operator= (const PlayerComponent& other) = default;
		PlayerComponent& operator= (PlayerComponent&& other) = default;
		void SetComponent(BaseComponent * comp) override;
		BaseComponent* Clone() override;
		void Initialize() override;
		void Update() override;
		void Render() const override;
		void TakeDamage(int amount);
		void Jump(float value);
		void Move(float value);
		void Fire(float value);
	public:
		RigidBodyComponent* m_Rigid;
		int m_Lives;
		float m_MovementSpeed;
		int m_GamepadID;
		FiniteStateMachine* m_FSM;
		SpriteSheetComponent* m_Sprite;
		std::vector<SpriteComponent*> m_BulletsPrefabs;
		int m_IdInput;
		bool m_Jump;
		bool m_Attack;
		float m_Moving;
	};

}


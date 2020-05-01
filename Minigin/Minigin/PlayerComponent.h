#pragma once
#include "BaseComponent.h"
#include "FiniteStateMachine.h"
namespace Rius
{
	class PlayerComponent :	public BaseComponent
	{
	public:
		PlayerComponent();
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
		void TakeDamage();
	public:
		int m_Lives;
		float m_MovementSpeed;
		int m_GamepadID;
		FiniteStateMachine* m_FSM;
	};

}


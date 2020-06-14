#pragma once
#include "BaseComponent.h"
#include "SpriteRenderer.h"
namespace Rius
{
	class TextureMaterial;
	class HealthComponent final : public BaseComponent
	{
	public:
		HealthComponent(int health, bool leftSide);
		~HealthComponent();

		HealthComponent(const HealthComponent& other) = default;
		HealthComponent(HealthComponent&& other) noexcept = default;
		HealthComponent& operator= (const HealthComponent& other) = default;
		HealthComponent& operator= (HealthComponent&& other) = default;
		
		void Initialize() override;
		void Update(float deltaT) override;
		void LateUpdate() override;
		void Render() const override;
		void RemoveHealth() { m_Health--; }
		void ResetHealth() { m_Health = m_OriginalHealth; }
		int CurrentHealth() const { return m_Health; }
	private:
		bool m_LeftSide;

		int m_Health;
		int m_OriginalHealth;

		TextureMaterial* m_pMat;
		SpriteRenderer* m_Sprites[10];
	};
}

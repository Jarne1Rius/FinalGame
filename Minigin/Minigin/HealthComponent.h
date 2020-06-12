#pragma once
#include "BaseComponent.h"
#include "SpriteRenderer.h"
namespace Rius
{
	class TextureMaterial;
	class HealthComponent :	public BaseComponent
	{
	public:
		HealthComponent(int health,bool leftSide);
		~HealthComponent();
		void Initialize() override;
		void Update(float deltatT) override;
		void Render() const override;
		void RemoveHealth() { m_Health--; }
		void ResetHealth() { m_Health = m_OriginalHealth; }
	private:
		TextureMaterial* m_pMat;
		SpriteRenderer* m_Sprites[3];
		int m_Health;
		int m_OriginalHealth;
		bool m_LeftSide;
	};
}

#pragma once

#include "Collider.h"
#include "Extra.h"

namespace Rius
{
	class CircleCollider2D final : public Collider
	{

	public:
		CircleCollider2D(Circle2D circle, bool IsTrigger = false);
		~CircleCollider2D();
		CircleCollider2D(const CircleCollider2D& other);
		CircleCollider2D(CircleCollider2D&& other) noexcept = default;
		CircleCollider2D& operator= (const CircleCollider2D& other) = default;
		CircleCollider2D& operator= (CircleCollider2D&& other) = default;
		void Initialize() override;
		void Update() override;
		void Render() const override;
		const Circle2D GetCircle2D()const { return m_Circle2D; }
		bool CheckCollision(CircleCollider2D* circle) override;
		bool CheckCollision(BoxCollider2D* collider) override;
		bool CheckCollision(BoxCollider3D* collider) override;
		bool CheckCollision(CircleCollider3D* circle) override;
		BaseComponent* Clone() override;
		void SetComponent(BaseComponent* comp) override;
		
	private:
		Circle2D m_Circle2D;
		bool m_Trigger;
	};
}

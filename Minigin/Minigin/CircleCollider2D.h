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
		void Initialize() override;
		void Update() override;
		void Render() const override;
		const Circle2D GetCircle2D()const { return m_Circle2D; }
		bool CheckCollision(CircleCollider2D* circle) override;
		bool CheckCollision(BoxCollider2D* collider) override;
		bool CheckCollision(BoxCollider3D* collider) override;
		bool CheckCollision(CircleCollider3D* circle) override;
	private:
		Circle2D m_Circle2D;
		bool m_Trigger;
	};
}
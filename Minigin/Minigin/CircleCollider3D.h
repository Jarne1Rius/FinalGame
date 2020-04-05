#pragma once
#include "Collider.h"
#include "Extra.h"

namespace Rius
{
	class CircleCollider3D : public Collider
	{
	public:
		CircleCollider3D(Circle3D circle, bool IsTrigger = false);
		~CircleCollider3D();
		void Initialize() override;
		void Update() override;
		void Render() const override;
		const Circle3D GetCircle3D()const { return m_Circle3D; }
		bool CheckCollision(CircleCollider2D* circle) override;
		bool CheckCollision(BoxCollider2D* collider) override;
		bool CheckCollision(CircleCollider3D* circle) override;
		bool CheckCollision(BoxCollider3D* collider) override;
	private:
		Circle3D m_Circle3D;
		bool m_Trigger;
	};

}


#pragma once
#include "Collider.h"
#include "Extra.h"

namespace Rius
{
	class CircleCollider3D : public Collider
	{
	public:
		CircleCollider3D(Circle3D circle, bool IsTrigger = false, CollisionGroup collisionGroup = Group0);
		~CircleCollider3D();
		CircleCollider3D(const CircleCollider3D& other);
		CircleCollider3D(CircleCollider3D&& other) noexcept = default;
		CircleCollider3D& operator= (const CircleCollider3D & other) = default;
		CircleCollider3D& operator= (CircleCollider3D && other) = default;
		BaseComponent* Clone() override;
		void SetComponent(BaseComponent* comp) override;
		
		void Initialize() override;
		void Update(float deltaT) override;
		void Render() const override;
		glm::vec2 GetCenter() override;
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


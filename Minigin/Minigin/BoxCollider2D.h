#pragma once
#include "Extra.h"
#include "Collider.h"
namespace Rius
{
	class CircleCollider2D;
	class BoxCollider2D : public Collider
	{
	public:
		BoxCollider2D(Rectangle2D rectangle, bool isTrigger = false);
		~BoxCollider2D();
		BoxCollider2D(const BoxCollider2D& other);
		BoxCollider2D(BoxCollider2D&& other) noexcept = default;
		BoxCollider2D& operator= (const BoxCollider2D& other) = default;
		BoxCollider2D& operator= (BoxCollider2D&& other) = default;
		void Initialize() override;
		void Update() override;
		void Render() const override;
		const Rectangle2D GetRectangle() const { return m_Rectangle; }
		bool CheckCollision(CircleCollider2D* circle) override;
		bool CheckCollision(BoxCollider2D* collider) override;
		bool CheckCollision(CircleCollider3D* circle)override;
		bool CheckCollision(BoxCollider3D* collider)override;
		BaseComponent* Clone() override;
		void SetComponent(BaseComponent* comp) override;
	private:
		Rectangle2D m_Rectangle;
	};
}

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
		void Initialize() override;
		void Update() override;
		void Render() const override;
		const Rectangle2D GetRectangle() const { return m_Rectangle; }
		bool CheckCollision(CircleCollider2D* circle) override;
		bool CheckCollision(BoxCollider2D* collider) override;
		bool CheckCollision(CircleCollider3D* circle)override;
		bool CheckCollision(BoxCollider3D* collider)override;
	private:
		Rectangle2D m_Rectangle;
	};
}

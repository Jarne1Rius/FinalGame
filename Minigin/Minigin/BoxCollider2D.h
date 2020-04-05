#pragma once
#include <map>
#include "Extra.h"
#include "Collider.h"
namespace Rius
{
	class CircleCollider2D;
	class BoxCollider2D : public Collider
	{
	public:
		BoxCollider2D();
		~BoxCollider2D();
		void Initialize() override;
		void Update() override;
		void Render() const override;
		const Rectangle2D GetRectangle() const { return m_Rectangle; }
		bool CheckCollision(CircleCollider2D* circle) override;
		bool CheckCollision(BoxCollider2D* collider) override;
	private:
		Rectangle2D m_Rectangle;
	};
}

#pragma once
#include "Collider.h"
#include  "Extra.h"
namespace Rius
{
	class CircleCollider3D;

	class BoxCollider3D : public Collider
	{
	public:
		BoxCollider3D(Rectangle3D rectangle, bool isTrigger = false);
		~BoxCollider3D();
		BoxCollider3D(const BoxCollider3D& other);
		BoxCollider3D(BoxCollider3D&& other) noexcept = default;
		BoxCollider3D& operator= (const BoxCollider3D & other) = default;
		BoxCollider3D& operator= (BoxCollider3D && other) = default;
		BaseComponent* Clone() override;
		void SetComponent(BaseComponent* comp) override;
		
		void Initialize() override;
		void Update() override;
		void Render() const override;
		const Rectangle3D GetRectangle() const { return m_Rectangle; }
		bool CheckCollision(CircleCollider2D* circle) override;
		bool CheckCollision(BoxCollider2D* collider) override;
		bool CheckCollision(CircleCollider3D* circle) override;
		bool CheckCollision(BoxCollider3D* collider) override;
	private:
		Rectangle3D m_Rectangle;
	};
}


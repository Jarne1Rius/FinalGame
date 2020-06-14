#pragma once
#include "Extra.h"
#include "Collider.h"
namespace Rius
{
	class CircleCollider2D;
	class BoxCollider2D final : public Collider
	{
	public:
		BoxCollider2D(Rectangle2D rectangle, const glm::vec2& center = { 0,0 }, bool isTrigger = false, CollisionGroup collisionGroup = Group0);
		~BoxCollider2D();
		BoxCollider2D(const BoxCollider2D& other);
		BoxCollider2D(BoxCollider2D&& other) noexcept = default;
		BoxCollider2D& operator= (const BoxCollider2D& other) = default;
		BoxCollider2D& operator= (BoxCollider2D&& other) = default;


		void Initialize() override;
		void Update(float deltaT) override;
		void Render() const override;
		glm::vec2 GetCenter() override;
		bool CheckCollision(CircleCollider2D* circle) override;
		bool CheckCollision(BoxCollider2D* collider) override;
		bool CheckCollision(CircleCollider3D* circle)override;
		bool CheckCollision(BoxCollider3D* collider)override;
		BaseComponent* Clone() override;
		void SetComponent(BaseComponent* comp) override;

		Rectangle2D GetRectangle() const { return m_Rectangle; }
	private:
		Rectangle2D m_Rectangle;
		glm::vec3 m_StartRectangle;
		glm::vec3 m_Center;
	};


}

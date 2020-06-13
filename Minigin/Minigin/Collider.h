#pragma once
#include <map>
#include "BaseComponent.h"

namespace Rius
{
	enum CollisionGroup
	{
		Group0,
		Group1,
		Group2,
		Group3,
	};
	class CircleCollider3D;
	class BoxCollider3D;
	class BoxCollider2D;
	class CircleCollider2D;
	class Collider : public BaseComponent
	{
	public:
		Collider(bool isTrigger, CollisionGroup collisionGroup);
		~Collider();
		Collider(const Collider& other) = default;
		Collider(Collider&& other) noexcept = default;
		Collider& operator= (const Collider& other) = default;
		Collider& operator= (Collider&& other) = default;


		void Initialize() override = 0;
		void Update(float deltaT) override = 0;

		void LateUpdate() override
		{
		}

		void Render() const override = 0;
		virtual glm::vec2 GetCenter() = 0;
		virtual bool CheckCollision(BoxCollider2D* collider) = 0;
		virtual bool CheckCollision(CircleCollider2D* circle) = 0;
		virtual bool CheckCollision(CircleCollider3D* circle) = 0;
		virtual bool CheckCollision(BoxCollider3D* collider) = 0;
		void DeleteCollider(Collider* collider);
		void AddCollider(Collider* collider);
		virtual BaseComponent* Clone() override = 0;
		virtual void SetComponent(BaseComponent* comp) override = 0;
		void SetStatic(bool isStatic) { m_Static = isStatic; }
		bool GetStatic() const { return m_Static; }
		void SetCollisions();
		void ChangeTrigger(bool isTrigger);
		static std::vector<Collider*> m_AllColliders;
		void SetIgnore(bool ignore = true);
		void SetIgnoreGroups(CollisionGroup group, bool ignore);
		void SetIgnoreGroups(bool ignore[Group3 + 1]);
		void SetCollisionGroup(CollisionGroup group);
		CollisionGroup GetCurrentCollisionGroup() const { return m_CurrentCollisionGroup; }
		bool IsTrigger() { return m_Trigger; }

		void SwitchToTrigger( bool trigger);
	private:

		static void AddColliderToAllColliders(Collider* collider);

		static void RemoveColliderOfAllColliders(Collider* collider);

	protected:
		bool m_IgnoreGroups[(CollisionGroup::Group3 + 1)] = { false, false, false, false };
		bool m_IgnoreCollisionGroup;
		CollisionGroup m_CurrentCollisionGroup;
		bool m_Static = false;
		glm::vec3 m_PreviousPos;
		bool m_Trigger;
		std::map<Collider*, bool> m_CollidersInCollision;
		bool m_PrevHit;
	};


}

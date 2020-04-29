#pragma once
#include <map>
#include "BaseComponent.h"

namespace Rius
{
	class CircleCollider3D;
	class BoxCollider3D;
	class BoxCollider2D;
	class CircleCollider2D;
	class Collider : public BaseComponent
	{
	public:
		Collider(bool isTrigger);
		~Collider();
		Collider(const Collider& other) = default;
		Collider(Collider&& other) noexcept = default;
		Collider& operator= (const Collider& other) = default;
		Collider& operator= (Collider&& other) = default;
		
		void Initialize() override = 0;
		void Update() override = 0;
		void Render() const override = 0;
		virtual bool CheckCollision(BoxCollider2D* collider) = 0;
		virtual bool CheckCollision(CircleCollider2D* circle) = 0;
		virtual bool CheckCollision(CircleCollider3D* circle) = 0;
		virtual bool CheckCollision(BoxCollider3D* collider) = 0;
		void DeleteCollider(Collider* collider);
		void AddCollider(Collider* collider);
		virtual BaseComponent* Clone() override = 0;
		virtual void SetComponent(BaseComponent* comp) override = 0;

		void SetCollisions();
		void ChangeTrigger(bool isTrigger);
		static std::vector<Collider*> m_AllColliders;
	protected:

		static void AddColliderToAllColliders(Collider* collider);
		
		static void RemoveColliderOfAllColliders(Collider* collider);
		
	protected:
		glm::vec3 m_PreviousPos;
		bool m_Trigger;
		std::map<Collider*, bool> m_CollidersInCollision;
	};

	
}

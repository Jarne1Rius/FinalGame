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
		void Initialize() override = 0;
		void Update() override = 0;
		void Render() const override = 0;
		virtual bool CheckCollision(BoxCollider2D* collider) = 0;
		virtual bool CheckCollision(CircleCollider2D* circle) = 0;
		virtual bool CheckCollision(CircleCollider3D* circle) = 0;
		virtual bool CheckCollision(BoxCollider3D* collider) = 0;
		void DeleteCollider(Collider* collider);
		void AddCollider(Collider* collider);

		void SetCollisions();
		void ChangeTrigger(bool isTrigger);
	protected:
		bool m_Trigger;
		std::map<Collider*, bool> m_CollidersInCollision;
	};

	
}

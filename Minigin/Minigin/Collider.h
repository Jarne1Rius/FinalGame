#pragma once
#include <map>

#include "BaseComponent.h"

namespace Rius
{
	class BoxCollider2D;
	class CircleCollider2D;
	class Collider : public BaseComponent
	{
	public:
		Collider();
		~Collider();
		void Initialize() override = 0;
		void Update() override = 0;
		void Render() const override = 0;
		virtual bool CheckCollision(BoxCollider2D* collider) = 0;
		virtual bool CheckCollision(CircleCollider2D* circle) = 0;
		void DeleteCollider(Collider* collider);
		void AddCollider(Collider* collider);
	protected:
		bool m_Trigger;
		std::map<Collider*, bool> m_CollidersInCollision;
	};

	
}

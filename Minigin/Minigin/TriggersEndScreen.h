#pragma once
#include "GameObject.h"
namespace Rius
{
	class BoxCollider2D;
	class TriggersEndScreen : public GameObject
	{
	public:
		TriggersEndScreen(const Rectangle2D& bottom, const Rectangle2D& top);
		~TriggersEndScreen();

		GameObject* Clone() override;
		void OnCollisionEnter(Collider* other) override;
	private:
		BoxCollider2D* m_pBottom;
		BoxCollider2D* m_pTop;
	};
}

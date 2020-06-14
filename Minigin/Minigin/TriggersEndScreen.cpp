#include "MiniginPCH.h"
#include "TriggersEndScreen.h"
#include "BoxCollider2D.h"
#include "Minigin.h"
#include "RigidBodyComponent.h"

Rius::TriggersEndScreen::TriggersEndScreen(const Rectangle2D& bottom, const Rectangle2D& top)
{
	m_pBottom = new BoxCollider2D{ bottom,{0,0},false, Group3 };
	m_pTop = new BoxCollider2D{ top ,{0,0},false, Group3};
	m_pRigidBodyComponent = new RigidBodyComponent{ 1 };
	AddComponent(m_pBottom);
	AddComponent(m_pTop);
	AddComponent(m_pRigidBodyComponent);
}

Rius::TriggersEndScreen::~TriggersEndScreen()
{
}

Rius::GameObject* Rius::TriggersEndScreen::Clone()
{
	return new TriggersEndScreen(m_pBottom->GetRectangle(), m_pTop->GetRectangle());
}


void Rius::TriggersEndScreen::OnCollisionEnter(Collider* other)
{
	if (other->GetGameObject()->GetTag() == Tag::Player || other->GetGameObject()->GetTag() == Tag::Enemy)
	{
		if (abs(other->GetGameObject()->GetTransform().GetPosition().y) < Minigin::m_Height / 2.f)
		{
			glm::vec3 newPos = { m_pTop->GetRectangle().pos ,0};
			other->GetGameObject()->GetTransform().Translate(newPos);
		}
	}
	//GameObject::OnCollisionEnter(other);
}

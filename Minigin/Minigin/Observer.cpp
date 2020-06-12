#include "MiniginPCH.h"
#include "Observer.h"
#include "UI.h"


Rius::Observer::Observer()
{
}

void Rius::Observer::OnNotify(const GameObject* object, Event event)
{
}

Rius::GUISystem::GUISystem( GameObject* pObject)
{
	pObject->AddObserver(this);
}

void Rius::GUISystem::OnNotify(const GameObject* object, Event event)
{
	switch (event)
	{
	case Event::hit:
		UI::GetInstance().GetPlayer(object).RemoveHealth();
		break;
	case Event::addscore:
		UI::GetInstance().GetPlayer(object).score += 10;
		break;
	}
}

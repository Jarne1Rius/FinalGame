#include "MiniginPCH.h"
#include "Observer.h"
#include "UI.h"
Rius::GUISystem::GUISystem(UI* ui)
	:m_MainUI(ui)
{
	
}

void Rius::GUISystem::OnNotify(const GameObject* object, Event event)
{
	switch (event)
	{
	case Event::hit:
		m_MainUI->GetPlayer(object).RemoveHealth();
		break;
	case Event::addscore:
		m_MainUI->GetPlayer(object).score += 10;
		break;
	}
}

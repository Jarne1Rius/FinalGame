#include "MiniginPCH.h"
#include "Observer.h"

#include "GameInstance.h"


Rius::Observer::Observer()
{
}

void Rius::Observer::OnNotify(GameObject* , Event )
{
}

Rius::GUISystem::GUISystem(GameObject* pObject)
{
	pObject->AddObserver(this);
}

void Rius::GUISystem::OnNotify(GameObject* object, Event event)
{
	switch (event)
	{
	case Event::hit:
		GameInstance::GetInstance().GetPlayer(object).RemoveHealth(1);
		break;
	case Event::addscore:
		GameInstance::GetInstance().GetPlayer(object).score += 10;
		break;
	default: ;
	}
}

Rius::MovingObjectObserver::MovingObjectObserver(GameObject* pObject)
{
	pObject->AddObserver(this);
}

void Rius::MovingObjectObserver::OnNotify(GameObject* object, Event event)
{
	switch (event)
	{
	case Event::AddEnemy:
		GameInstance::GetInstance().AddEnemy(object);
		break;
	case Event::AddPlayer:
		GameInstance::GetInstance().AddPlayer(object);
		break;
	case Event::RemoveEnemy:
		GameInstance::GetInstance().RemoveEnemy(object);
		break;
	default: ;
	}
}

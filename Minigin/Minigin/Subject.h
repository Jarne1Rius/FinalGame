#pragma once
#include "Observer.h"

#define MAX_Observer  10
namespace Rius
{
	class Subject
	{
	public:
		Subject();
		virtual ~Subject();
		virtual void AddObserver(Observer* observer);
		virtual void RemoveObserver(Observer* observer);
		virtual void Notify(GameObject* gameobject, Event event);
	private:
		Observer* m_pObservers[MAX_Observer];
		int m_NumOfObservers = 0;
	};
}

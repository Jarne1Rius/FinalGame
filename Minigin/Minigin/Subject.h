#pragma once
#include "Observer.h"
#define MAx_Observer  10
namespace Rius
{
	class Subject
	{
	public:
		Subject();
		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);
		void Notify(const GameObject* gameobject, Event event);
	private:
		Observer* m_pObservers[MAx_Observer];
		int m_NumOfObservers = 2;
	};
}

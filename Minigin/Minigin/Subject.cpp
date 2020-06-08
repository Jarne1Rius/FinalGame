#include "MiniginPCH.h"
#include "Subject.h"

Rius::Subject::Subject()
{
}

void Rius::Subject::AddObserver(Observer* observer)
{
	m_NumOfObservers++;
	m_pObservers[m_NumOfObservers] = observer;
}

void Rius::Subject::RemoveObserver(Observer* observer)
{
	for (int i = 0; i < m_NumOfObservers; ++i)
	{
		if (m_pObservers[i] == observer)
		{
			m_pObservers[i] = m_pObservers[m_NumOfObservers];
			break;
		}
	}
	m_NumOfObservers--;

}

void Rius::Subject::Notify(const GameObject* gameobject, Event event)
{
	for (int i = 0; i < m_NumOfObservers; ++i)
	{
		m_pObservers[i]->OnNotify(gameobject, event);
	}
}

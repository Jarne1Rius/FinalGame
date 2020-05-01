#include "MiniginPCH.h"
#include "State.h"
#include "FiniteStateMachine.h"
#include "Logger.h"
//Transition
Rius::Transition::Transition(std::function<bool()> trans, StateClass* fromState, StateClass* nextState)
{
	m_transition = trans;
	m_NextState = nextState;
	m_FromState = fromState;
	m_FromState->AddTransition(this);
}

Rius::StateClass* Rius::Transition::CheckState()
{
	if(m_transition() == true)
	{
		return this->m_NextState;
	}
	return m_FromState;
}

//State


Rius::StateClass::StateClass()
{
}

Rius::StateClass::~StateClass()
{
	for (int i = 0; i < int(m_Transitions.size()); ++i)
	{
		delete m_Transitions[i];
	}
}

void Rius::StateClass::AddTransition(Transition* transition)
{
	m_Transitions.push_back(transition);
}

void Rius::StateClass::AddTransitions(std::vector<Transition*> transitions)
{
	for (Transition* transition : transitions)
	{
		m_Transitions.push_back(transition);
	}
}

Rius::StateClass* Rius::StateClass::UpdateState()
{
	for (Transition* transition : m_Transitions)
	{
		StateClass* newone = transition->CheckState();
		if(newone != this) return newone;
	}
	return this;
}

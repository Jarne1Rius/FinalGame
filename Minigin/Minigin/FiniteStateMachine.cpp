#include "MiniginPCH.h"
#include "FiniteStateMachine.h"

Rius::FiniteStateMachine::FiniteStateMachine(std::vector<StateClass*> allStates)
{
	m_CurrentState = allStates[0];
	m_States = allStates;
}

Rius::FiniteStateMachine::~FiniteStateMachine()
{
	for (int i = 0; i < int(m_States.size()); ++i)
	{
		delete m_States[i];
	}
}

void Rius::FiniteStateMachine::UpdateState()
{
	m_CurrentState = m_CurrentState->UpdateState();
}

void Rius::FiniteStateMachine::AddTransitions(std::vector<Transition*> transitions, StateClass* addState)
{
	m_CurrentState->AddTransitions(transitions);
}
#include "MiniginPCH.h"
#include "FiniteStateMachine.h"

Rius::FiniteStateMachine::FiniteStateMachine(std::vector<State*> allStates)
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
	m_States.clear();
}

void Rius::FiniteStateMachine::UpdateState()
{
	m_CurrentState = m_CurrentState->UpdateState();
}

void Rius::FiniteStateMachine::AddTransitionsTo(std::function<bool()> trans, std::vector<State*> states, State* toState)
{
	for (auto state : states)
	{
		state->AddTransition(trans, toState);
	}
}

void Rius::FiniteStateMachine::AddActionTo(std::function<void()> action, std::vector<State*> states)
{
	for (auto state : states)
	{
		state->AddAction(action);
	}
}

void Rius::FiniteStateMachine::AddEndActionTo(std::function<void()> endAction, std::vector<State*> states)
{
	for (auto state : states)
	{
		state->AddActionEnd(endAction);
	}
}

void Rius::FiniteStateMachine::AddStartActionTo(std::function<void()> startAction, std::vector<State*> states)
{
	for (auto state : states)
	{
		state->AddActionStart(startAction);
	}
}

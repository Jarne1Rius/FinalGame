#include "MiniginPCH.h"
#include "State.h"
#include "FiniteStateMachine.h"
#include "Logger.h"


//Transition
Rius::Transition::Transition(std::function<bool()> trans,  State* nextState)
{
	m_Transition = trans;
	m_NextState = nextState;
}

Rius::State* Rius::Transition::CheckState()
{
	if (m_Transition() == true)
	{
		return this->m_NextState;
	}
	return nullptr;
}


//State

Rius::State::State(std::string name)
	:m_Name(name)
{
}

Rius::State::~State()
{
	for (int i = 0; i < int(m_Transitions.size()); ++i)
	{
		delete m_Transitions[i];
	}
}

void Rius::State::SetTransition(std::function<bool()> transtionfunction, State* nextState)
{
	m_Transitions.push_back(new Transition{ transtionfunction,nextState });
}

void Rius::State::SetAction(std::function<void()> action)
{
	m_Actions.push_back(action );
}

void Rius::State::SetActionEnd(std::function<void()> action)
{
	m_EndActions.push_back(action);
}

void Rius::State::SetActionStart(std::function<void()> action)
{
	m_StartActions.push_back(action);
}

Rius::State* Rius::State::UpdateState()
{
	for (auto action : m_Actions)
	{
		action();
	}
	for (Transition* transition : m_Transitions)
	{
		State* newone = transition->CheckState();
		if (newone != nullptr) return newone;
	}
	return this;
}

void Rius::State::StartState()
{
	for (auto action : m_StartActions)
	{
		action();
	}
}

void Rius::State::EndState()
{
	for (auto action : m_EndActions)
	{
		action();
	}
}

#include "MiniginPCH.h"
#include "State.h"
#include "FiniteStateMachine.h"
#include "Logger.h"

Rius::Action::Action(std::function<void()> action, StateClass* state)
{
	m_Action = action;
	state->AddAction(this);
}

void Rius::Action::Update()
{
	m_Action();
}

//Transition
Rius::Transition::Transition(std::function<bool()> trans, StateClass* fromState, StateClass* nextState)
{
	m_Transition = trans;
	m_NextState = nextState;
	m_FromState = fromState;
	m_FromState->AddTransition(this);
}

Rius::StateClass* Rius::Transition::CheckState()
{
	if(m_Transition() == true)
	{
		return this->m_NextState;
	}
	return m_FromState;
}

//State


Rius::StateClass::StateClass(std::string name)
	:m_Name(name)
{
}

Rius::StateClass::~StateClass()
{
	for (int i = 0; i < int(m_Transitions.size()); ++i)
	{
		delete m_Transitions[i];
	}
	for (int i = 0; i < int(m_Actions.size()); ++i)
	{
		delete m_Actions[i];
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

void Rius::StateClass::AddActions(std::vector<Action*> actions)
{
	for (Action* action : actions)
	{
		m_Actions.push_back(action);
	}
}

void Rius::StateClass::AddAction(Action* action)
{
	m_Actions.push_back(action);
}

Rius::StateClass* Rius::StateClass::UpdateState()
{
	for (Action* action : m_Actions)
	{
		action->Update();
	}
	for (Transition* transition : m_Transitions)
	{
		StateClass* newone = transition->CheckState();
		if(newone != this) return newone;
	}
	return this;
}

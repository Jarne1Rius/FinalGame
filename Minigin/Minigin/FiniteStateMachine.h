#pragma once
#include "State.h"
namespace Rius
{
	class FiniteStateMachine
	{
	public:
		FiniteStateMachine(std::vector<StateClass*> allStates);
		~FiniteStateMachine();
		void UpdateState();
		void AddTransitions(std::vector<Transition*> transitions, StateClass* addState);
		StateClass* m_CurrentState;
	private:
		std::vector<StateClass*> m_States;
	};

	
}

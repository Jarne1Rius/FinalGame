#pragma once
#include "State.h"
namespace Rius
{
	class FiniteStateMachine
	{
	public:
		FiniteStateMachine(std::vector<State*> allStates);
		~FiniteStateMachine();
		void UpdateState();
		State* m_CurrentState;
	private:
		std::vector<State*> m_States;
	};

	
}

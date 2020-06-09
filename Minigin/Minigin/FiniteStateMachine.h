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
		void AddTransitionsTo(std::function<bool()> trans, std::vector<State*> states, State* toState);
		void AddActionTo(std::function<void()> action, std::vector<State*> states);
		void AddEndActionTo(std::function<void()> endAction, std::vector<State*> states);
		void AddStartActionTo(std::function<void()> startAction, std::vector<State*> states);
	private:
		std::vector<State*> m_States;
	};

	
}

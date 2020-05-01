#pragma once
#include <vector>
#include <functional>
namespace Rius
{
	class StateClass;
	/*enum State
	{
		Menu, InGame, TwoPlayer, Lost, Won, NextLevel
	};*/
	
	class Transition
	{
	public:
		explicit Transition(std::function<bool()> trans, StateClass* fromState,StateClass* nextState);
		StateClass* CheckState();
		void SetCurrentState(StateClass* state) { m_FromState = state; };
	private:
		std::function<bool()> m_transition;
		StateClass* m_FromState;
		StateClass* m_NextState;
	};
	class StateClass
	{
	public:
		StateClass();
		~StateClass();
		void AddTransition(Transition* transition);
		void AddTransitions(std::vector<Transition*> transitions);
		StateClass* UpdateState();
	private:
		std::vector<Transition*> m_Transitions;
	};

	

}
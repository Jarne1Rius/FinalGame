#pragma once
#include <vector>
#include <functional>
namespace Rius
{
	class StateClass;
	class Action
	{
	public:
		Action(std::function<void()> action, StateClass* state);
		void Update();
	private:
		std::function<void()> m_Action;
	};
	
	class Transition
	{
	public:
		explicit Transition(std::function<bool()> trans, StateClass* fromState, StateClass* nextState);
		StateClass* CheckState();
		void SetCurrentState(StateClass* state) { m_FromState = state; };
	private:
		std::function<bool()> m_Transition;
		StateClass* m_FromState;
		StateClass* m_NextState;
	};
	class StateClass
	{
	public:
		StateClass(std::string name);
		~StateClass();
		void AddTransition(Transition* transition);
		void AddTransitions(std::vector<Transition*> transitions);
		void AddActions(std::vector<Action*> actions);
		void AddAction(Action* action);
		StateClass* UpdateState();
		const char* GetName() { return m_Name.c_str(); }
	private:
		std::string m_Name;
		std::vector<Transition*> m_Transitions;
		std::vector<Action*> m_Actions;
	};



}
#pragma once
#include <vector>
#include <functional>
namespace Rius
{
	class State;
	class Transition
	{
	public:
		explicit Transition(std::function<bool()> trans, State* nextState);
		State* CheckState();
	private:
		std::function<bool()> m_Transition;
		State* m_NextState;
	};
	class State
	{
	public:
		State(std::string name);
		~State();
		void AddTransition(std::function<bool()> transtionfunction, State* nextState);
		void AddAction(std::function<void()> action);
		void AddActionEnd(std::function<void()> action);
		void AddActionStart(std::function<void()> action);
		State* UpdateState();
		void StartState();
		void EndState();
		const char* GetName() { return m_Name.c_str(); }
	private:
		std::string m_Name;
		std::vector<Transition*> m_Transitions;
		std::vector<std::function<void()>> m_Actions;
		std::vector<std::function<void()>> m_StartActions;
		std::vector<std::function<void()>> m_EndActions;
	};



}
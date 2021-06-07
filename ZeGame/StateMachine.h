#pragma once
#include <vector>
#include "EBlackboard.h"
#include <memory>

namespace qbert
{
//	class Data
//	{
//	public:
//		Data();
//		~Data();
//		void AddData(int id,)
//	private:
//	};
	
	class State
	{
	public:
		State(Elite::Blackboard* pB, int id) { m_pB = pB; m_Id = id; };
		virtual ~State() = default;
		virtual void OnEnter() = 0;
		virtual void Update(float dt) = 0;
		virtual void OnExit() = 0;
		int GetId() { return m_Id; };
	protected:
		Elite::Blackboard* m_pB;
		int m_Id;
	};

	class Transition
	{
	public:
		Transition(Elite::Blackboard* pB) { m_pB = pB; };
		virtual ~Transition() = default;
		virtual bool ChangeState() = 0;
	protected:
		Elite::Blackboard* m_pB;
	};

	class FSM final
	{
	public:
		FSM(std::shared_ptr<State> pStartState);
		~FSM();

		void Update(float dt);
		void AddTransition(std::shared_ptr<State> pStartState, std::shared_ptr<State> pEndState, std::shared_ptr<Transition> pTransition);
		int GetCurrentStateId();
	private:
		std::vector<std::pair<std::pair<std::shared_ptr<State>, std::shared_ptr<State>>, std::shared_ptr<Transition>>> m_Pairs;
		std::shared_ptr<State> m_pCurrentState;
	};
}


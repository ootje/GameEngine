#include "StateMachine.h"


qbert::FSM::FSM(std::shared_ptr<State> pStartState)
{
	m_pCurrentState = pStartState;
	m_Pairs = std::vector<std::pair<std::pair<std::shared_ptr<State>,std::shared_ptr<State>>,std::shared_ptr<Transition>>>();
}
qbert::FSM::~FSM()
{
	for (auto& element : m_Pairs)
	{
		element.first.first.reset();
		element.first.second.reset();
		element.second.reset();
	}
}

void qbert::FSM::Update(float dt)
{
	for (auto& element : m_Pairs)
	{
		if (element.first.first == m_pCurrentState)
		{
			if (element.second->ChangeState())
			{
				element.first.first->OnExit();
				m_pCurrentState = element.first.second;
				element.first.second->OnEnter();
				break;
			}
		}
	}
	m_pCurrentState->Update(dt);
}


void qbert::FSM::AddTransition(std::shared_ptr<State> pStartState, std::shared_ptr<State> pEndState, std::shared_ptr<Transition> pTransition)
{
	m_Pairs.push_back(std::make_pair(std::make_pair(pStartState, pEndState), pTransition));
}

int qbert::FSM::GetCurrentStateId()
{
	return m_pCurrentState->GetId();
}

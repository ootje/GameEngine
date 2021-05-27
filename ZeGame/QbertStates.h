#pragma once
#include "StateMachine.h"
#include "Helpers.h"

namespace qbert
{
	class QbertIdle final : public State
	{
	public:
		QbertIdle(Elite::Blackboard* pB, int id);
		~QbertIdle() override;
		void OnEnter() override;
		void Update(float dt) override;
		void OnExit() override;
	};

	class QbertJumping final :public State
	{
	public:
		QbertJumping(Elite::Blackboard* pB, int id);
		~QbertJumping() override;
		void OnEnter() override;
		void Update(float dt) override;
		void OnExit() override;
	private:
		position m_Direction;
		position m_Target;
	};

	class QbertDeath final : public State
	{
	public:
		QbertDeath(Elite::Blackboard* pB, int id);
		~QbertDeath() override;
		void OnEnter() override;
		void Update(float dt) override;
		void OnExit() override;
	};

	class QbertTeleporting final : public State
	{
	public:
		QbertTeleporting(Elite::Blackboard* pB,int id);
		~QbertTeleporting() override;
		void OnEnter() override;
		void Update(float dt) override;
		void OnExit() override;
	};
}


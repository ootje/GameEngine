#pragma once
#include "StateMachine.h"

namespace qbert
{
	class ToJumping final : public Transition
	{
	public:
		ToJumping(Elite::Blackboard* pB);
		~ToJumping() override;
		bool ChangeState() override;
	};

	class ToIdle final :public Transition
	{
	public:
		ToIdle(Elite::Blackboard* pB);
		~ToIdle() override;
		bool ChangeState() override;
	};

	class ToTeleport final : public Transition
	{
	public:
		ToTeleport(Elite::Blackboard* pB);
		~ToTeleport() override;
		bool ChangeState() override;
	};

	class ToDeath final : public qbert::Transition
	{
	public:
		ToDeath(Elite::Blackboard* pB);
		~ToDeath() override;
		bool ChangeState() override;
	};
}


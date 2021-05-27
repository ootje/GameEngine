#pragma once
#include "StateMachine.h"

namespace qbert
{
	class IdleToJumping final : public Transition
	{
	public:
		IdleToJumping(Elite::Blackboard* pB);
		~IdleToJumping() override;
		bool ChangeState() override;
	};

	class JumpingToIdle final :public Transition
	{
	public:
		JumpingToIdle(Elite::Blackboard* pB);
		~JumpingToIdle() override;
		bool ChangeState() override;
	};

	class JumpingToTeleport final : public Transition
	{
	public:
		JumpingToTeleport(Elite::Blackboard* pB);
		~JumpingToTeleport() override;
		bool ChangeState() override;
	};

	class TeleportToIdle final : public Transition
	{
	public:
		TeleportToIdle(Elite::Blackboard* pB);
		~TeleportToIdle() override;
		bool ChangeState() override;
	};

	class JumpToDeath final : public Transition
	{
	public:
		JumpToDeath(Elite::Blackboard* pB);
		~JumpToDeath() override;
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


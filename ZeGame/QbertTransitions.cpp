#include "QbertTransitions.h"
#include "Helpers.h"

qbert::IdleToJumping::IdleToJumping(Elite::Blackboard* pB)
	:Transition(pB)
{
	
}
qbert::IdleToJumping::~IdleToJumping()
{
	
}
bool qbert::IdleToJumping::ChangeState()
{
	int* newIdPos = nullptr;
	int* oldIdPos = nullptr;
	bool check = m_pB->GetData("OldIdPos", oldIdPos);
	check = check && m_pB->GetData("NewIdPos", newIdPos);
	
	if (!check)
	{
		return false;
	}
	
	return *newIdPos != *oldIdPos;
}

qbert::JumpingToIdle::JumpingToIdle(Elite::Blackboard* pB)
	:Transition(pB)
{
	
}
qbert::JumpingToIdle::~JumpingToIdle()
{
	
}
bool qbert::JumpingToIdle::ChangeState()
{
	int* newIdPos = nullptr;
	int* oldIdPos = nullptr;
	bool check = m_pB->GetData("OldIdPos", oldIdPos);
	check = check && m_pB->GetData("NewIdPos", newIdPos);

	if (!check)
	{
		return false;
	}
	if (*newIdPos == *oldIdPos)
	{
		if (IsValidIdPosition(*newIdPos))
		{
			return true;
		}
	}
	return false;
}

qbert::JumpingToTeleport::JumpingToTeleport(Elite::Blackboard* pB)
	:Transition(pB)
{
	
}
qbert::JumpingToTeleport::~JumpingToTeleport()
{
	
}
bool qbert::JumpingToTeleport::ChangeState()
{
	int* newIdPos = nullptr;
	int* oldIdPos = nullptr;
	bool check = m_pB->GetData("OldIdPos", oldIdPos);
	check = check && m_pB->GetData("NewIdPos", newIdPos);

	if (!check)
	{
		return false;
	}
	if (*newIdPos == *oldIdPos)
	{
		if (IsOnTeleport(*oldIdPos))
		{
			return true;
		}
	}
	return false;
}

qbert::TeleportToIdle::TeleportToIdle(Elite::Blackboard* pB)
	:Transition(pB)
{
	
}
qbert::TeleportToIdle::~TeleportToIdle()
{
	
}
bool qbert::TeleportToIdle::ChangeState()
{
	int* newIdPos = nullptr;
	int* oldIdPos = nullptr;
	bool check = m_pB->GetData("OldIdPos", oldIdPos);
	check = check && m_pB->GetData("NewIdPos", newIdPos);

	if (!check)
	{
		return false;
	}
	if (*newIdPos == *oldIdPos)
	{
		if (IsValidIdPosition(*oldIdPos))
		{
			return true;
		}
	}
	return false;
}

qbert::JumpToDeath::JumpToDeath(Elite::Blackboard* pB)
	:Transition(pB)
{
	
}
qbert::JumpToDeath::~JumpToDeath()
{
	
}
bool qbert::JumpToDeath::ChangeState()
{
	return false;
}

qbert::ToDeath::ToDeath(Elite::Blackboard* pB)
	:Transition(pB)
{
	
}
qbert::ToDeath::~ToDeath()
{
	
}
bool qbert::ToDeath::ChangeState()
{
	return false;
}
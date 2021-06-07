#include "QbertTransitions.h"
#include "Helpers.h"

qbert::ToJumping::ToJumping(Elite::Blackboard* pB)
	:Transition(pB)
{
	
}
qbert::ToJumping::~ToJumping()
{
	
}
bool qbert::ToJumping::ChangeState()
{
	id* newIdPos = nullptr;
	id* oldIdPos = nullptr;
	bool check = m_pB->GetData("OldIdPos", oldIdPos);
	check = check && m_pB->GetData("NewIdPos", newIdPos);
	
	if (!check)
	{
		return false;
	}
	
	return (newIdPos->x != oldIdPos->x) || (newIdPos->y != oldIdPos->y);
}

qbert::ToIdle::ToIdle(Elite::Blackboard* pB)
	:Transition(pB)
{
	
}
qbert::ToIdle::~ToIdle()
{
	
}
bool qbert::ToIdle::ChangeState()
{
	id* newIdPos = nullptr;
	id* oldIdPos = nullptr;
	bool check = m_pB->GetData("OldIdPos", oldIdPos);
	check = check && m_pB->GetData("NewIdPos", newIdPos);

	if (!check)
	{
		return false;
	}
	if (*newIdPos == *oldIdPos)
	{
		return IsValidIdPositionEnemy(*newIdPos);
	}
	return false;
}

qbert::ToTeleport::ToTeleport(Elite::Blackboard* pB)
	:Transition(pB)
{
	
}
qbert::ToTeleport::~ToTeleport()
{
	
}
bool qbert::ToTeleport::ChangeState()
{
	id* newIdPos = nullptr;
	id* oldIdPos = nullptr;
	bool check = m_pB->GetData("OldIdPos", oldIdPos);
	check = check && m_pB->GetData("NewIdPos", newIdPos);

	if (!check)
	{
		return false;
	}
	if (*newIdPos == *oldIdPos)
	{
		return IsOnTeleport(*oldIdPos);
	}
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
	id* newIdPos = nullptr;
	id* oldIdPos = nullptr;
	bool* isDead = nullptr;
	bool check = m_pB->GetData("OldIdPos", oldIdPos);
	check = check && m_pB->GetData("NewIdPos", newIdPos);
	check = check && m_pB->GetData("IsDead", isDead);

	if (!check)
	{
		return false;
	}
	if (*isDead)
	{
		*isDead = false;
		return true;
	}
	if (*newIdPos == *oldIdPos)
	{
		return !IsValidIdPosition(*newIdPos); // return NOT ValidPosition
	}
	return false;
}
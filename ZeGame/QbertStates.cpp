#include "QbertStates.h"

#include <iostream>

qbert::QbertIdle::QbertIdle(Elite::Blackboard* pB, int id)
	:State(pB,id)
{
	
}
qbert::QbertIdle::~QbertIdle()
{
	
}
void qbert::QbertIdle::OnEnter()
{
	std::cout << "Entering QbertIdle\n";
}
void qbert::QbertIdle::Update(float)
{
	
}
void qbert::QbertIdle::OnExit()
{
	
}

qbert::QbertJumping::QbertJumping(Elite::Blackboard* pB, int id)
	:State(pB,id)
{
	
}
qbert::QbertJumping::~QbertJumping()
{
	
}
void qbert::QbertJumping::OnEnter()
{
	std::cout << "Entering QbertJumping\n";
	int* newIdpos = nullptr;
	int* oldIdpos = nullptr;
	position* qbertPosition = nullptr;
	float* qbertWidth = nullptr;
	bool check = m_pB->GetData("NewIdPos", newIdpos);
	check = check && m_pB->GetData("OldIdPos", oldIdpos);
	check = check && m_pB->GetData("QbertPos", qbertPosition);
	check = check && m_pB->GetData("QbertWidth", qbertWidth);
	if (!check)
	{
		return;
	}
	m_Target = IdToPositionConverter(*newIdpos);
	m_Target.x -= (*qbertWidth) / 2.0f;
	m_Direction = position{ m_Target.x - qbertPosition->x,m_Target.y - qbertPosition->y };
	//float size = sqrtf(m_Direction.x * m_Direction.x + m_Direction.y * m_Direction.y);
	//m_Direction.x /= size;
	//m_Direction.y /= size;
}
void qbert::QbertJumping::Update(float dt)
{
	int* newIdpos = nullptr;
	int* oldIdpos = nullptr;
	position* qbertPosition = nullptr;
	bool check = m_pB->GetData("NewIdPos", newIdpos);
	check = check && m_pB->GetData("OldIdPos", oldIdpos);
	check = check && m_pB->GetData("QbertPos", qbertPosition);
	if (!check)
	{
		return;
	}
	qbertPosition->x += m_Direction.x * dt;
	qbertPosition->y += m_Direction.y * dt;
	float distance = abs(m_Target.x - qbertPosition->x) + abs(m_Target.y - qbertPosition->y);
	if (distance < 1.0f)
	{
		*qbertPosition = m_Target;
		*oldIdpos = *newIdpos;
	}
	
}
void qbert::QbertJumping::OnExit()
{
	
}

qbert::QbertDeath::QbertDeath(Elite::Blackboard* pB, int id)
	:State(pB,id)
{
	
}
qbert::QbertDeath::~QbertDeath()
{
	
}
void qbert::QbertDeath::OnEnter()
{
	std::cout << "Entering QbertDeath\n";
}
void qbert::QbertDeath::Update(float)
{
	
}
void qbert::QbertDeath::OnExit()
{
	
}

qbert::QbertTeleporting::QbertTeleporting(Elite::Blackboard* pB, int id)
	:State(pB,id)
{
	
}
qbert::QbertTeleporting::~QbertTeleporting()
{
	
}
void qbert::QbertTeleporting::OnEnter()
{
	std::cout << "Entering QbertTeleporting\n";
}
void qbert::QbertTeleporting::Update(float)
{
	
}
void qbert::QbertTeleporting::OnExit()
{
	
}



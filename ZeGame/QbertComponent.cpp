#include "QbertComponent.h"
#include "RenderComponent.h"
#include "StateMachine.h"
#include "QbertStates.h"
#include "QbertTransitions.h"

enum class EQbertStates : int
{
	idle = 0,
	jumping = 1,
	teleporting = 2,
	death = 3,
};


qbert::QbertComponent::QbertComponent(dae::RenderComponent* pRender, int startId, float width)
	:m_IdNewPosition(startId)
	,m_IdOldPosition(startId)
	,m_pRenderComp(pRender)
	,m_Width(width)
{
	m_Position = IdToPositionConverter(startId);
	m_Position.x -= width / 2.0f;
	m_pRenderComp->ChangePosition(m_Position.x, m_Position.y);

	InitializeFSM();
}

void qbert::QbertComponent::InitializeFSM()
{
	m_pBb = new Elite::Blackboard();

	m_pBb->AddData("OldIdPos", &m_IdOldPosition);
	m_pBb->AddData("NewIdPos", &m_IdNewPosition);
	m_pBb->AddData("QbertPos", &m_Position);
	m_pBb->AddData("QbertWidth", &m_Width);
	
	auto idle = std::make_shared<QbertIdle>(QbertIdle(m_pBb, (int)EQbertStates::idle));
	auto jumping = std::make_shared<QbertJumping>(QbertJumping(m_pBb,(int)EQbertStates::jumping));
	auto death = std::make_shared<QbertDeath>(QbertDeath(m_pBb, (int)EQbertStates::death));
	auto teleport = std::make_shared<QbertTeleporting>(QbertTeleporting(m_pBb, (int)EQbertStates::teleporting));

	m_pFSM = new FSM(idle);
	
	auto idleToJump = std::make_shared<IdleToJumping>(IdleToJumping(m_pBb));
	auto jumpToIdle = std::make_shared<JumpingToIdle>(JumpingToIdle(m_pBb));
	m_pFSM->AddTransition(idle, jumping, idleToJump);
	m_pFSM->AddTransition(jumping, idle, jumpToIdle);

	auto jumpToTeleport = std::make_shared<JumpingToTeleport>(JumpingToTeleport(m_pBb));
	auto teleportToIdle = std::make_shared<TeleportToIdle>(TeleportToIdle(m_pBb));
	m_pFSM->AddTransition(jumping, teleport, jumpToTeleport);
	m_pFSM->AddTransition(teleport, idle, teleportToIdle);

	auto toDeath = std::make_shared<ToDeath>(ToDeath(m_pBb));
	m_pFSM->AddTransition(idle, death, toDeath);
	m_pFSM->AddTransition(jumping, death, toDeath);
	m_pFSM->AddTransition(teleport, death, toDeath);
}

qbert::QbertComponent::~QbertComponent()
{
	m_pRenderComp = nullptr;
	delete(m_pFSM);
	delete(m_pBb);
}

void qbert::QbertComponent::Update(float dt)
{
	m_pFSM->Update(dt);
	if (m_pFSM->GetCurrentStateId() != (int)EQbertStates::idle)
	{
		m_pRenderComp->ChangePosition(m_Position.x, m_Position.y);
	}
}


void qbert::QbertComponent::Move(int movePosition)
{
	if (m_pFSM->GetCurrentStateId() == (int)EQbertStates::idle)
	{
		m_IdNewPosition = m_IdOldPosition + movePosition;
	}
}
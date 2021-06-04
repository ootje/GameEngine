#include "QbertComponent.h"
#include "RenderComponent.h"
#include "StateMachine.h"
#include "QbertStates.h"
#include "QbertTransitions.h"
#include "Subject.h"

enum class EQbertStates : int
{
	idle = 0,
	jumping = 1,
	teleporting = 2,
	death = 3,
};


qbert::QbertComponent::QbertComponent(dae::RenderComponent* pRender, id startId, float width, dae::Subject* pScore, dae::Subject* pLives)
	:m_IdNewPosition(startId)
	,m_IdOldPosition(startId)
	,m_pRenderComp(pRender)
	,m_Width(width)
	,m_pLivesSubject(pLives)
	,m_pScoreSubject(pScore)
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
	m_pBb->AddData("QbertLives", &m_pLivesSubject);
	
	auto idle = std::make_shared<QbertIdle>(QbertIdle(m_pBb, (int)EQbertStates::idle));
	auto jumping = std::make_shared<QbertJumping>(QbertJumping(m_pBb,(int)EQbertStates::jumping));
	auto death = std::make_shared<QbertDeath>(QbertDeath(m_pBb, (int)EQbertStates::death));
	auto teleport = std::make_shared<QbertTeleporting>(QbertTeleporting(m_pBb, (int)EQbertStates::teleporting));

	m_pFSM = new FSM(idle);
	
	auto toJump = std::make_shared<ToJumping>(ToJumping(m_pBb));
	auto toIdle = std::make_shared<ToIdle>(ToIdle(m_pBb));
	m_pFSM->AddTransition(idle, jumping, toJump);
	m_pFSM->AddTransition(jumping, idle, toIdle);

	auto toTeleport = std::make_shared<ToTeleport>(ToTeleport(m_pBb));
	m_pFSM->AddTransition(jumping, teleport, toTeleport);
	m_pFSM->AddTransition(teleport, idle, toIdle);

	auto toDeath = std::make_shared<ToDeath>(ToDeath(m_pBb));
	m_pFSM->AddTransition(idle, death, toDeath);
	m_pFSM->AddTransition(jumping, death, toDeath);
	m_pFSM->AddTransition(teleport, death, toDeath);

	m_pFSM->AddTransition(death, idle, toIdle);
}

qbert::QbertComponent::~QbertComponent()
{
	m_pRenderComp = nullptr;
	delete(m_pFSM);
	delete(m_pBb);
	delete(m_pLivesSubject);
	delete(m_pScoreSubject);
}

void qbert::QbertComponent::Update(float dt)
{
	m_pFSM->Update(dt);
	if (m_pFSM->GetCurrentStateId() != (int)EQbertStates::idle)
	{
		m_pRenderComp->ChangePosition(m_Position.x, m_Position.y);
	}
}


void qbert::QbertComponent::Move(id movePosition)
{
	if (m_pFSM->GetCurrentStateId() == (int)EQbertStates::idle)
	{
		m_IdNewPosition.x = m_IdOldPosition.x + movePosition.x;
		m_IdNewPosition.y = m_IdOldPosition.y + movePosition.y;
	}
}
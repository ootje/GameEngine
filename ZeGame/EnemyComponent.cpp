#include "EnemyComponent.h"
#include "RenderComponent.h"


qbert::EnemyComponent::EnemyComponent(id startId, float size, EnemyBehaviour* pBehaviour, dae::RenderComponent* pRendercomp, bool isPurple, bool isReverting)
	:m_OldId(startId)
	,m_NewId(startId)
	,m_Size(size)
	,m_pBehaviour(pBehaviour)
	,m_pRenderComp(pRendercomp)
	,m_IsPurple(isPurple)
	,m_IsRevertingTiles(isReverting)
{
	m_Position = IdToPositionConverter(startId);
	position offset = m_Position;
	offset.x -= size / 2.0f;
	
	m_pRenderComp->ChangePosition(offset.x, offset.y);
}
qbert::EnemyComponent::~EnemyComponent()
{
	
}
void qbert::EnemyComponent::Update(float dt)
{
	if (m_OldId == m_NewId)
	{
		m_NewId = m_pBehaviour->CalculateNextMove(m_OldId);
	}
	else
	{
		position oldPos = IdToPositionConverter(m_OldId);
		position newPos = IdToPositionConverter(m_NewId);
		float distance = abs(newPos.x - oldPos.x) + abs(newPos.y - oldPos.y);
		if (distance < 1.0f)
		{
			m_OldId = m_NewId;
			m_Position = newPos;
			if (m_IsRevertingTiles)
			{
				//Something here
			}
		}
		else
		{
			position direction{ newPos.x - oldPos.x,newPos.y - oldPos.y };
			m_Position.x += direction.x * dt;
			m_Position.y += direction.y * dt;
		}


		m_pRenderComp->ChangePosition(m_Position.x + m_Size / 2.0f, m_Position.y);
	}

	
}

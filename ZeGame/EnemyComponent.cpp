#include "EnemyComponent.h"

#include "LevelManager.h"
#include "RenderComponent.h"


qbert::EnemyComponent::EnemyComponent(id startId, float size, EnemyBehaviour* pBehaviour, dae::RenderComponent* pRendercomp, bool isPurple, bool isReverting)
	:m_OldId(startId)
	,m_NewId(startId)
	,m_StartId(startId)
	,m_Size(size)
	,m_pBehaviour(pBehaviour)
	,m_pRenderComp(pRendercomp)
	,m_IsPurple(isPurple)
	,m_IsRevertingTiles(isReverting)
	,m_IsActive(false)
{
	m_Position = IdToPositionConverter(startId);
	position offset = m_Position;
	offset.x -= size / 2.0f;
	
	m_pRenderComp->ChangePosition(offset.x, offset.y);
}
qbert::EnemyComponent::~EnemyComponent()
{
	delete(m_pBehaviour);
}
void qbert::EnemyComponent::Update(float dt)
{
	if (!m_IsActive)
	{
		return;
	}
	
	if (m_OldId == m_NewId)
	{
		if (!IsValidIdPositionEnemy(m_OldId))
		{
			Deactivate();
			return;
		}
		m_NewId = m_pBehaviour->CalculateNextMove(m_OldId);
		m_Elapsed = 0.0f;
	}
	else
	{
		position oldPos = IdToPositionConverter(m_OldId);
		position newPos = IdToPositionConverter(m_NewId);
		float distance = abs(newPos.x - oldPos.x) + abs(newPos.y - oldPos.y);
		if (distance < 1.0f || (m_Elapsed>1.1f))
		{
			m_OldId = m_NewId;
			m_Position = newPos;
			if (m_IsRevertingTiles)
			{
				//Something here
				LevelManager::GetInstance().RevertTile(m_OldId);
			}
		}
		else
		{
			m_Elapsed += dt;
			position direction{ newPos.x - oldPos.x,newPos.y - oldPos.y };
			m_Position.x += direction.x * dt*0.9f;
			m_Position.y += direction.y * dt*0.9f;
		}


		m_pRenderComp->ChangePosition(m_Position.x - m_Size / 2.0f, m_Position.y);
	}

	
}

bool qbert::EnemyComponent::HandleColision(position pos, float width, float height)
{
	if (!m_IsActive)
	{
		return false;
	}
	if (IsPointInCharacter(pos.x-width/2.0f,pos.y)||
		IsPointInCharacter(pos.x+width/2.0f,pos.y)||
		IsPointInCharacter(pos.x - width / 2.0f, pos.y + height)||
		IsPointInCharacter(pos.x + width / 2.0f, pos.y + height))
		if (m_IsPurple)
		{
			return true;
		}
		else
		{
			Deactivate();
		}
	return false;
}

bool qbert::EnemyComponent::IsPointInCharacter(float x, float y)
{
	float enemySize = m_Size / 2.0f;
	float enemyX = m_Position.x - enemySize/2.0f;
	float enemY = m_Position.y + enemySize / 2.0f;
	if (enemyX< x && x < enemyX+enemySize)
	{
		if (enemY < y && y < enemY+enemySize)
		{
			return true;
		}
	}
	return false;
}


void qbert::EnemyComponent::Activate()
{
	m_IsActive = true;
	m_NewId = m_StartId;
	m_OldId = m_StartId;
	m_Position = IdToPositionConverter(m_StartId);
	m_pRenderComp->ChangePosition(m_Position.x + m_Size / 2.0f, m_Position.y);
	m_pRenderComp->SetActive(true);
}

void qbert::EnemyComponent::Deactivate()
{
	m_IsActive = false;
	m_pRenderComp->SetActive(false);
	int event = m_pBehaviour->EventOnDeath();
	if (event != -1)
	{
		LevelManager::GetInstance().ScoreEvent(event);
	}
}



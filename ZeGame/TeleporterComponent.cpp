#include "TeleporterComponent.h"
#include <RenderComponent.h>

qbert::TeleporterComponent::TeleporterComponent(id position, dae::RenderComponent* pRenderer, float size)
	:m_Position(IdToPositionConverter(position))
	,m_Id(position)
	,m_Available(true)
	,m_Renderer(pRenderer)
	,m_Moving(false)
	,m_Size(size)
{
	pRenderer->ChangePosition(m_Position.x - size / 2.0f, m_Position.y+size);
}

void qbert::TeleporterComponent::Activate()
{
	m_Available = false;
	m_Moving = true;
}

void qbert::TeleporterComponent::Update(float dt)
{
	if (m_Moving)
	{
		m_Position.y -= dt*100.f;
		m_Renderer->ChangePosition(m_Position.x - m_Size / 2.0f, m_Position.y+m_Size);
		if (m_Position.y < 0.0f)
		{
			m_Moving = false;
			m_Renderer->SetActive(false);
		}
	}
}

void qbert::TeleporterComponent::Reset()
{
	m_Available = true;
	m_Moving = false;
	m_Position = IdToPositionConverter(m_Id);
	m_Renderer->ChangePosition(m_Position.x - m_Size / 2.0f, m_Position.y+m_Size);
	m_Renderer->SetActive(true);
}





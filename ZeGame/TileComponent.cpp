#include "TileComponent.h"
#include "TileRenderComponent.h"

qbert::TileComponent::TileComponent(id id,TileRenderComponent* renderComp,int maxLandings, bool resetOnOverflow)
	:m_Id(id)
	,m_Activations(0)
	,m_MaxActivations(maxLandings)
	,m_ResetOnLanding(resetOnOverflow)
	,m_RenderComponent(renderComp)
	,m_ColorOffset(0)
{
	
}
qbert::TileComponent::~TileComponent()
{
	
}

void qbert::TileComponent::Update(float)
{
	
}
void qbert::TileComponent::Render() const
{
	
}

void qbert::TileComponent::GetJumpedOn()
{
	if (m_Activations == m_MaxActivations)
	{
		if (m_ResetOnLanding)
		{
			m_Activations = 0;
			m_RenderComponent->ChangeTileColor(m_Activations+m_ColorOffset);
		}
	}
	else
	{
		m_Activations++;
		m_RenderComponent->ChangeTileColor(m_Activations+m_ColorOffset);
	}
}

qbert::id qbert::TileComponent::GetId() const
{
	return m_Id;
}
bool qbert::TileComponent::IsComplete() const
{
	return m_Activations == m_MaxActivations;
}

void qbert::TileComponent::Deactivate()
{
	if (m_Activations > 0)
	{
		m_Activations--;
		m_RenderComponent->ChangeTileColor(m_Activations + m_ColorOffset);
	}
}

void qbert::TileComponent::Reset(int activations, bool reset,int colorOffset)
{
	m_MaxActivations = activations;
	m_ResetOnLanding = reset;
	m_Activations = 0;
	m_ColorOffset = colorOffset;
	m_RenderComponent->ChangeTileColor(colorOffset);
}

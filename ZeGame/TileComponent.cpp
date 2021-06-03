#include "TileComponent.h"
#include "TileRenderComponent.h"

qbert::TileComponent::TileComponent(id id,TileRenderComponent* renderComp,int maxLandings, bool resetOnOverflow)
	:m_Id(id)
	,m_Activations(0)
	,m_MaxActivations(maxLandings)
	,m_ResetOnLanding(resetOnOverflow)
	,m_RenderComponent(renderComp)
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
			m_RenderComponent->ChangeTileColor();
		}
	}
	else
	{
		m_Activations++;
		m_RenderComponent->ChangeTileColor();
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
#include "TileComponent.h"


qbert::TileComponent::TileComponent(int id, int maxLandings, bool resetOnOverflow)
	:m_Id(id)
	,m_Activations(0)
	,m_MaxActivations(maxLandings)
	,m_ResetOnLanding(resetOnOverflow)
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
		}
	}
	else
	{
		m_Activations++;
	}
}
int qbert::TileComponent::GetId() const
{
	return m_Id;
}
bool qbert::TileComponent::IsComplete() const
{
	return m_Activations == m_MaxActivations;
}
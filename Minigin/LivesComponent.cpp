#include "MiniginPCH.h"
#include "LivesComponent.h"


LivesComponent::LivesComponent(TextComponent* pTextComp,Observer* pObserver)
	:m_Lives{100}
{
	m_pText = pTextComp;
	m_pObserver = pObserver;
	std::string text = "Lives: " + std::to_string(m_Lives);
	m_pText->SetText(text);
}
LivesComponent::~LivesComponent()
{
}

void LivesComponent::Update(float)
{
	if (m_pObserver->GetSize() > 0)
	{
		if (m_pObserver->GetNextEvent() == dae::Event::Event_Player_Died)
		{
			m_Lives -= 1;
			std::string text = "Lives: " + std::to_string(m_Lives);
			m_pText->SetText(text);
		}
	}
}
void LivesComponent::Render() const
{

}
#include "LivesComponent.h"

#include <string>

#include "LevelManager.h"
#include "LivesObserver.h"

qbert::LivesComponent::LivesComponent(dae::TextComponent* pTextComp, LivesObserver* pObserver)
	:m_Lives{3}
{
	m_pText = pTextComp;
	m_pObserver = pObserver;
	std::string text = "Lives: " + std::to_string(m_Lives);
	m_pText->SetText(text);
}
qbert::LivesComponent::~LivesComponent()
{
	
}

void qbert::LivesComponent::Update(float)
{
	/*if (m_pObserver->GetSize() > 0)
	{
		if (m_pObserver->GetNextEvent() == dae::Event::Event_Player_Died)
		{
			m_Lives -= 1;
			std::string text = "Lives: " + std::to_string(m_Lives);
			m_pText->SetText(text);
		}
	}*/
}
void qbert::LivesComponent::Render() const
{

}

void qbert::LivesComponent::LoseLife()
{
	m_Lives--;
	std::string text = "Lives: " + std::to_string(m_Lives);
	m_pText->SetText(text);
	if (m_Lives < 0)
	{
		LevelManager::GetInstance().QbertDeath();
		//something
	}
	
}

void qbert::LivesComponent::Reset()
{
	m_Lives = 3;
	std::string text = "Lives: " + std::to_string(m_Lives);
	m_pText->SetText(text);
}


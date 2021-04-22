#include "MiniginPCH.h"
#include "ScoreComponent.h"


ScoreComponent::ScoreComponent(TextComponent* pTextComp, Observer* pObserver)
	:m_Score{ 0 }
{
	m_pText = pTextComp;
	m_pObserver = pObserver;
	std::string text = "Score: " + std::to_string(m_Score);
	m_pText->SetText(text);
}
ScoreComponent::~ScoreComponent()
{
}

void ScoreComponent::Update(float)
{
	if (m_pObserver->GetSize() > 0)
	{
		if ((int)m_pObserver->GetNextEvent() > 0 )
		{
			m_Score += 25;
			std::string text = "Score: " + std::to_string(m_Score);
			m_pText->SetText(text);
		}
	}
}
void ScoreComponent::Render() const
{

}

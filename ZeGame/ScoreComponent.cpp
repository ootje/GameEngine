#include "ScoreComponent.h"
#include <string>

#include "ScoreObserver.h"
#include "TextComponent.h"

qbert::ScoreComponent::ScoreComponent(dae::TextComponent* pTextComp, ScoreObserver* pObserver)
	:m_Score{ 0 }
{
	m_pText = pTextComp;
	m_pObserver = pObserver;
	std::string text = "Score: " + std::to_string(m_Score);
	m_pText->SetText(text);
}
qbert::ScoreComponent::~ScoreComponent()
{
	
}

void qbert::ScoreComponent::Update(float)
{
	/*if (m_pObserver->GetSize() > 0)
	{
		if ((int)m_pObserver->GetNextEvent() > 0 )
		{
			m_Score += 25;
			std::string text = "Score: " + std::to_string(m_Score);
			m_pText->SetText(text);
		}
	}*/
}
void qbert::ScoreComponent::Render() const
{

}

void qbert::ScoreComponent::AddScore(int score)
{
	m_Score += score;
	std::string text = "Score: " + std::to_string(m_Score);
	m_pText->SetText(text);
}

void qbert::ScoreComponent::Reset()
{
	m_Score = 0;
	std::string text = "Score: " + std::to_string(m_Score);
	m_pText->SetText(text);
}

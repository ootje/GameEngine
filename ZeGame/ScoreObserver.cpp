#include "ScoreObserver.h"
#include "ScoreComponent.h"
#include "Helpers.h"
//
//qbert::ScoreObserver::ScoreObserver()
//{
//	m_pScoreComp = nullptr;
//}


void qbert::ScoreObserver::AttachScoreComp(ScoreComponent* pScoreComp)
{
	m_pScoreComp = pScoreComp;
}

void qbert::ScoreObserver::OnNotify(dae::BaseComponent*, int event)
{
	int score = 0;
	qbertEvents ev = qbertEvents(event);
	switch (ev)
	{
	case qbertEvents::ADD_SCORE_25:
		score = 25;
		break;
	case qbertEvents::ADD_SCORE_50:
		score = 50;
		break;
	case qbertEvents::ADD_SCORE_300:
		score = 300;
		break;
	case qbertEvents::ADD_SCORE_500:
		score = 500;
		break;
	}
	m_pScoreComp->AddScore(score);
}


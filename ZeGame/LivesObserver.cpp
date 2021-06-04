#include "LivesObserver.h"
#include "Helpers.h"
#include "LivesComponent.h"

qbert::LivesObserver::LivesObserver()
{
	m_pLiveComp = nullptr;
}


void qbert::LivesObserver::AttachLivesComp(LivesComponent* pLivesComp)
{
	m_pLiveComp = pLivesComp;
}


void qbert::LivesObserver::OnNotify(dae::BaseComponent* , int event)
{
	qbertEvents ev = qbertEvents(event);

	switch (ev)
	{
	case qbertEvents::LOSE_LIFE:
		m_pLiveComp->LoseLife();
		break;
	}
}
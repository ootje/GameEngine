#include "MiniginPCH.h"
#include "Subject.h"

Subject::Subject()
{

}
Subject::~Subject()
{
	delete(m_pObserver);
}

void Subject::Attach(Observer* observer)
{
	m_pObserver = observer;
}
void Subject::Notify(dae::Event event)
{
	if (m_pObserver != nullptr)
	{
		m_pObserver->OnNotify(event);
	}
}
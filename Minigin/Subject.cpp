#include "MiniginPCH.h"
#include "Subject.h"

dae::Subject::Subject()
{

}
dae::Subject::~Subject()
{
	delete(m_pObserver);
}

void dae::Subject::Attach(Observer* observer)
{
	m_pObserver = observer;
}
void dae::Subject::Notify(dae::Event event)
{
	if (m_pObserver != nullptr)
	{
		m_pObserver->OnNotify(event);
	}
}
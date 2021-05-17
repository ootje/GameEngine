#include "MiniginPCH.h"
#include "Observer.h"

dae::Observer::Observer()
{
	m_Events = std::queue<dae::Event>();
}
dae::Observer::~Observer()
{

}

int dae::Observer::GetSize() const
{
	return (int)m_Events.size();
}

void dae::Observer::Update()
{

}

// Get next event and remove from queue
dae::Event dae::Observer::GetNextEvent()
{
	dae::Event event = m_Events.front();
	m_Events.pop();
	return event;
}

void dae::Observer::OnNotify(dae::Event event)
{
	m_Events.push(event);
}
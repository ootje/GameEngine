#include "MiniginPCH.h"
#include "Observer.h"

Observer::Observer()
{
	m_Events = std::queue<dae::Event>();
}
Observer::~Observer()
{

}

int Observer::GetSize() const
{
	return (int)m_Events.size();
}

void Observer::Update()
{

}

// Get next event and remove from queue
dae::Event Observer::GetNextEvent()
{
	dae::Event event = m_Events.front();
	m_Events.pop();
	return event;
}

void Observer::OnNotify(dae::Event event)
{
	m_Events.push(event);
}
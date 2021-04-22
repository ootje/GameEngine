#pragma once
#include <queue>

namespace dae
{
	enum class Event
	{
		Event_Player_Died,
		Event_Player_25,
		Event_Player_50,
		Event_Player_300,
		Event_Player_500,
	};
}


class Observer
{
public:
	Observer();
	~Observer();

	void Update();
	void OnNotify(dae::Event event);

	dae::Event GetNextEvent();

	int GetSize() const;

	Observer(const Observer& other) = delete;
	Observer(Observer&& other) = delete;
	Observer& operator=(const Observer& other) = delete;
	Observer& operator=(Observer&& other) = delete;

private:
	std::queue<dae::Event> m_Events;
};


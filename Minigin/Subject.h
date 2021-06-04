#pragma once
#include "Observer.h"

namespace dae
{
	class Subject final
	{
	public:
		Subject();
		~Subject();

		void Attach(Observer* observer);
		void Notify(BaseComponent* pEntityComp, int event);

		Subject(const Subject& other) = delete;
		Subject(Subject&& other) = delete;
		Subject& operator=(const Subject& other) = delete;
		Subject& operator=(Subject&& other) = delete;

	private:
		Observer* m_pObserver = nullptr;
	};
}


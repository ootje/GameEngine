#pragma once
#include <queue>

#include "BaseComponent.h"


namespace dae
{
	class Observer
	{
	public:
		Observer() = default;
		virtual ~Observer() {};
		
		virtual void OnNotify(BaseComponent* pEntityComp, int event) = 0;

		Observer(const Observer& other) = delete;
		Observer(Observer&& other) = delete;
		Observer& operator=(const Observer& other) = delete;
		Observer& operator=(Observer&& other) = delete;
	};
}





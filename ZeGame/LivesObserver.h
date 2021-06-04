#pragma once
#include "Observer.h"

namespace qbert
{
	class LivesComponent;

	class LivesObserver final : public dae::Observer
	{
	public:
		LivesObserver();
		~LivesObserver() override {};

		void AttachLivesComp(LivesComponent* pLivesComp);
		void OnNotify(dae::BaseComponent* pEntityComp, int event) override;

	private:
		LivesComponent* m_pLiveComp;
	};
}


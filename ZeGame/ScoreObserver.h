#pragma once
#include "Observer.h"

namespace qbert
{
	class ScoreComponent;

	class ScoreObserver final : public dae::Observer
	{
	public:
		ScoreObserver(){};
		~ScoreObserver() override {};

		void AttachScoreComp(ScoreComponent* pScoreComp);
		void OnNotify(dae::BaseComponent* pEntityComp, int event) override;

	private:
		ScoreComponent* m_pScoreComp = nullptr;
	};
}


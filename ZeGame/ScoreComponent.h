#pragma once
#include "BaseComponent.h"
#include "TextComponent.h"

namespace qbert
{
	class ScoreObserver;

	class ScoreComponent final : public dae::BaseComponent
	{
	public:
		ScoreComponent(dae::TextComponent* pTextComp, ScoreObserver* pObserver);
		~ScoreComponent();


		void AddScore(int score);
		void Update(float dt) override;
		void Render() const override;

	private:
		int m_Score;
		dae::TextComponent* m_pText;
		ScoreObserver* m_pObserver;
	};
}


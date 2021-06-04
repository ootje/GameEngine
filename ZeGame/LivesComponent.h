#pragma once
#include "BaseComponent.h"
#include "TextComponent.h"

namespace qbert
{
	class LivesObserver;

	class LivesComponent final : public dae::BaseComponent
	{
	public:
		LivesComponent(dae::TextComponent* pTextComp, LivesObserver* pObserver);
		~LivesComponent();

		void LoseLife();
		
		void Update(float dt) override;
		void Render() const override;

	private:
		int m_Lives;
		dae::TextComponent* m_pText;
		LivesObserver* m_pObserver;
	};
}


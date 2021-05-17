#pragma once
#include "BaseComponent.h"
#include "TextComponent.h"
#include "Observer.h"

class LivesComponent final : public BaseComponent
{
public:
	LivesComponent(TextComponent* pTextComp, dae::Observer* pObserver);
	~LivesComponent();

	void Update(float dt) override;
	void Render() const override;

private:
	int m_Lives;
	TextComponent* m_pText;
	dae::Observer* m_pObserver;
};


#pragma once
#include "BaseComponent.h"
#include "TextComponent.h"
#include "Observer.h"

class ScoreComponent : public BaseComponent
{
public:
	ScoreComponent(TextComponent* pTextComp, Observer* pObserver);
	~ScoreComponent();

	void Update(float dt) override;
	void Render() const override;

private:
	int m_Score;
	TextComponent* m_pText;
	Observer* m_pObserver;
};


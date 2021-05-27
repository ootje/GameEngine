#pragma once
//#include "BaseComponent.h"
#include "TextComponent.h"

class FPSComponent final : public dae::BaseComponent
{
public:
	FPSComponent(const std::string& text, const std::shared_ptr<dae::Font>& font, float x, float y);
	virtual ~FPSComponent();

	virtual void Update(float dt) override;
	virtual void Render() const override;

	int GetFPS() const;

private:
	TextComponent m_TextComponent;
	int m_FPS;
	float m_Timer;
};


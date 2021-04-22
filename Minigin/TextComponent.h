#pragma once
#include "BaseComponent.h"
#include "TextObject.h"

class TextComponent final : public BaseComponent
{
public:
	TextComponent(const std::string& text, const std::shared_ptr<dae::Font>& font, float x, float y);
	virtual ~TextComponent();

	virtual void Update(float) override;
	virtual void Render() const override;

	void SetText(const std::string& text);

	TextComponent(const TextComponent& other) = delete;
	TextComponent(TextComponent&& other) = delete;
	TextComponent& operator=(const TextComponent& other) = delete;
	TextComponent& operator=(TextComponent&& other) = delete;

private:
	dae::TextObject* m_pText;
};

#include "MiniginPCH.h"
#include "TextComponent.h"

TextComponent::TextComponent(const std::string& text, const std::shared_ptr<dae::Font>& font, float x, float y)
{
	m_pText = new dae::TextObject(text, font);
	m_pText->SetPosition(x, y);
}

TextComponent::~TextComponent()
{
	delete(m_pText);
}

void TextComponent::Update(float)
{
	m_pText->Update();
}

void TextComponent::Render() const
{
	m_pText->Render();
}

void TextComponent::SetText(const std::string& text)
{
	m_pText->SetText(text);
}
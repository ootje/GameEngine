#include "MiniginPCH.h"
#include "TextComponent.h"

dae::TextComponent::TextComponent(const std::string& text, const std::shared_ptr<dae::Font>& font, float x, float y)
{
	m_pText = new dae::TextObject(text, font);
	m_pText->SetPosition(x, y);
}

dae::TextComponent::~TextComponent()
{
	delete(m_pText);
}

void dae::TextComponent::Update(float)
{
	m_pText->Update();
}

void dae::TextComponent::Render() const
{
	m_pText->Render();
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_pText->SetText(text);
}
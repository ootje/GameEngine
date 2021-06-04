#include "MiniginPCH.h"
#include "FPSComponent.h"

dae::FPSComponent::FPSComponent(const std::string& text, const std::shared_ptr<dae::Font>& font, float x, float y)
	:m_TextComponent{text,font,x,y}
	, m_FPS{0}
	,m_Timer{0.f}
{
}
dae::FPSComponent::~FPSComponent()
{

}

void dae::FPSComponent::Update(float dt)
{
	int fps = int(1 / dt);
	std::string text = std::to_string(fps);
	text += "fps";
	m_TextComponent.SetText(text);
	/*m_FPS++;
	m_Timer += dt;*/
	/*if (m_Timer >= 1.f)
	{
		m_Timer -= 1.f;
		std::string text = std::to_string(fps);
		text += "fps";
		m_TextComponent.SetText(text);
		m_FPS = 0;
	}*/
	m_TextComponent.Update(dt); //BAD
}
void dae::FPSComponent::Render() const
{
	m_TextComponent.Render();
}

int dae::FPSComponent::GetFPS() const
{
	return m_FPS;
}
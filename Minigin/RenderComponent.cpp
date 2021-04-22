#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "SDL.h"
#include "Texture2D.h"
#include "ResourceManager.h"

RenderComponent::RenderComponent(const std::string& texturePath, float x, float y, float width, float height)
	:m_X{x}
	,m_Y{y}
	,m_Width{width}
	,m_Height{height}
{
	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(texturePath);
}
RenderComponent::RenderComponent(const std::string& texturePath, float x, float y)
	:m_X{ x }
	, m_Y{ y }
	, m_Width{ 0.f }
	, m_Height{ 0.f }
{
	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(texturePath);
}
RenderComponent::~RenderComponent()
{

}

void RenderComponent::Update(float)
{

}

void RenderComponent::Render() const
{
	if (m_Width == 0.f || m_Height == 0.f)
		dae::Renderer::GetInstance().RenderTexture(*m_pTexture.get(), m_X, m_Y);
	else
		dae::Renderer::GetInstance().RenderTexture(*m_pTexture.get(),m_X,m_Y,m_Width,m_Height);
}

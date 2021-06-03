#include "TileRenderComponent.h"

#include <string>

#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"


qbert::TileRenderComponent::TileRenderComponent(int size, float x, float y, float width, float height, int colorOffset)
	:m_Size(size)
	,m_Active(0)
	,m_X(x)
	,m_Y(y)
	,m_Width(width)
	,m_Height(height)
{
	for (int i = 0 + colorOffset; i < size+colorOffset; i++)
	{
		std::string path = "Cube_" + std::to_string(i) + ".png";
		m_Textures.push_back(dae::ResourceManager::GetInstance().LoadTexture(path));
	}
}
qbert::TileRenderComponent::~TileRenderComponent()
{
	for (auto elem : m_Textures)
	{
		elem.reset();
	}
}

void qbert::TileRenderComponent::ChangeTileColor()
{
	m_Active = (m_Active + 1) % m_Size;
}

void qbert::TileRenderComponent::Update(float)
{
	
}

void qbert::TileRenderComponent::Render() const
{
	dae::Renderer::GetInstance().RenderTexture(*m_Textures[m_Active], m_X, m_Y, m_Width, m_Height);
}

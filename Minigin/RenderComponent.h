#pragma once
#include "BaseComponent.h"
#include "Renderer.h"

class RenderComponent final : public BaseComponent
{
public:
	RenderComponent(const std::string& texturePath, float x, float y, float width, float height); 
	RenderComponent(const std::string& texturePath, float x, float y);
	virtual ~RenderComponent();

	virtual void Update(float) override;
	virtual void Render() const override;

	RenderComponent(const RenderComponent& other) = delete;
	RenderComponent(RenderComponent&& other) = delete;
	RenderComponent& operator=(const RenderComponent& other) = delete;
	RenderComponent& operator=(RenderComponent&& other) = delete;
private:
	std::shared_ptr<dae::Texture2D> m_pTexture = nullptr;
	float m_X;
	float m_Y;
	float m_Width;
	float m_Height;
};

#pragma once
#include <memory>
#include <vector>

#include "BaseComponent.h"

namespace dae {
	class Texture2D;
}

namespace qbert
{
	class TileRenderComponent final : public dae::BaseComponent
	{
	public:
		TileRenderComponent(int size, float x, float y ,float width, float height);
		~TileRenderComponent() override;

		void Update(float dt) override;
		void Render() const override;
		
		void ChangeTileColor(int activation);
	
	private:
		int m_Active;
		int m_Size;
		float m_X;
		float m_Y;
		float m_Width;
		float m_Height;
		std::vector<std::shared_ptr<dae::Texture2D>> m_Textures;
	};
}


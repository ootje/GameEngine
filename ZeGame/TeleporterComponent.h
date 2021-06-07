#pragma once
#include "BaseComponent.h"
#include "Helpers.h"

namespace dae {
	class RenderComponent;
}

namespace qbert
{
	class TeleporterComponent final : public dae::BaseComponent
	{
	public:
		TeleporterComponent(id position, dae::RenderComponent* pRender, float size);
		~TeleporterComponent() override {};

		void Update(float dt) override;
		void Render() const override{};

		void Reset();
		void Activate();
		bool GetAvailable() const
		{
			return m_Available;
		}
		id GetId() const
		{
			return m_Id;
		}
	
	private:
		id m_Id;
		position m_Position;
		bool m_Available;
		bool m_Moving;
		float m_Size;
		dae::RenderComponent* m_Renderer;
	};
}


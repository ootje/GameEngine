#pragma once
#include "BaseComponent.h"
#include "Helpers.h"

namespace qbert
{
	class TeleporterComponent final : public dae::BaseComponent
	{
	public:
		TeleporterComponent(id position);
		~TeleporterComponent() override {};

		void Update(float dt) override;
		void Render() const override;

		bool GetAvailable() const
		{
			return m_Available;
		}
		position GetPosition() const
		{
			return m_Position;
		}
	
	private:
		id m_Id;
		position m_Position;
		bool m_Available;
	};
}


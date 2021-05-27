#pragma once

#include "BaseComponent.h"

namespace qbert
{
	class TileComponent final : public dae::BaseComponent
	{
	public:
		TileComponent(int id,int maxLandings = 1,bool resetOnOverflow = false);
		~TileComponent();
		
		void Update(float dt) override;
		void Render() const override;

		void GetJumpedOn();
		int GetId() const;
		bool IsComplete() const;
	private:
		int m_Id;
		int m_Activations; // 0 is off, max is m_MaxActivations
		int m_MaxActivations;
		bool m_ResetOnLanding;
	};
}


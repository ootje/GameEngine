#pragma once

#include <vector>

#include "BaseComponent.h"
#include "Helpers.h"

namespace qbert
{
	class TileRenderComponent;

	class TileComponent final : public dae::BaseComponent
	{
	public:
		TileComponent(id id, TileRenderComponent* renderComp,int maxLandings = 1,bool resetOnOverflow = false);
		~TileComponent();
		
		void Update(float dt) override;
		void Render() const override;

		void GetJumpedOn();
		void Deactivate();
		id GetId() const;
		bool IsComplete() const;
		void Reset(int activations,bool reset, int colorOffset);
	private:
		id m_Id;
		int m_Activations; // 0 is off, max is m_MaxActivations
		int m_MaxActivations;
		bool m_ResetOnLanding;
		TileRenderComponent* m_RenderComponent;
		int m_ColorOffset;
	};
}


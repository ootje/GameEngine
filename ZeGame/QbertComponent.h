#pragma once
#include "BaseComponent.h"
#include "Helpers.h"

namespace Elite {
	class Blackboard;
}

namespace dae {
	class RenderComponent;
}

namespace qbert
{
	class FSM;
	
	class QbertComponent : public dae::BaseComponent
	{
	public:
		QbertComponent(dae::RenderComponent* pRender, int startId, float width);
		~QbertComponent() override;

		void Update(float dt) override;
		void Render() const override {};
		
		void Move(int movePosition);
	private:
		void InitializeFSM();
		
		int m_IdNewPosition;
		int m_IdOldPosition;
		position m_Position;
		dae::RenderComponent* m_pRenderComp;
		FSM* m_pFSM;
		Elite::Blackboard* m_pBb;
		float m_Width;
	};
}


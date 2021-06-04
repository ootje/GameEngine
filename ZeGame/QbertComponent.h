#pragma once
#include "BaseComponent.h"
#include "Helpers.h"

namespace Elite {
	class Blackboard;
}

namespace dae {
	class Subject;
	class RenderComponent;
}

namespace qbert
{
	class FSM;
	
	class QbertComponent : public dae::BaseComponent
	{
	public:
		QbertComponent(dae::RenderComponent* pRender, id startId, float width, dae::Subject* pScore, dae::Subject* pLives);
		~QbertComponent() override;

		void Update(float dt) override;
		void Render() const override {};
		
		void Move(id movePosition);
		id GetOldId() const { return m_IdOldPosition; }
	private:
		void InitializeFSM();
		
		id m_IdNewPosition;
		id m_IdOldPosition;
		position m_Position;
		dae::RenderComponent* m_pRenderComp;
		FSM* m_pFSM;
		Elite::Blackboard* m_pBb;
		float m_Width;

		dae::Subject* m_pLivesSubject;
		dae::Subject* m_pScoreSubject;
	};
}


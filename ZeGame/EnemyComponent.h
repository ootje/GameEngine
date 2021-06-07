#pragma once
#include <BaseComponent.h>
#include "EnemyBehaviour.h"
#include "Helpers.h"

namespace dae {
	class RenderComponent;
}

namespace qbert
{
	class EnemyComponent final : public dae::BaseComponent
	{
	public:
		EnemyComponent(id startId,float size,EnemyBehaviour* pBehaviour, dae::RenderComponent* pRendercomp , bool isPurple, bool isReverting = false);
		~EnemyComponent() override;

		void Update(float dt) override;
		void Render() const override{};

		bool HandleColision(position pos, float width, float height);
		void Deactivate();
		void Activate();
		bool GetIsActive() const { return m_IsActive; }
		
		bool IsPurple() const { return m_IsPurple; }
	private:
		bool IsPointInCharacter(float x, float y);

		id m_StartId;
		id m_OldId;
		id m_NewId;
		position m_Position;
		float m_Size;
		bool m_IsPurple;
		EnemyBehaviour* m_pBehaviour = nullptr;
		bool m_IsRevertingTiles;
		dae::RenderComponent* m_pRenderComp;
		bool m_IsActive;
		float m_Elapsed;
	};
}


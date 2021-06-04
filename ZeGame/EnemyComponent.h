#pragma once
#include <BaseComponent.h>
#include "EnemyBehaviour.h"
#include "Helpers.h"

namespace dae {
	class RenderComponent;
}

namespace qbert
{
	class EnemyComponent : public dae::BaseComponent
	{
	public:
		EnemyComponent(id startId,float size,EnemyBehaviour* pBehaviour, dae::RenderComponent* pRendercomp , bool isPurple, bool isReverting = false);
		~EnemyComponent() override;

		void Update(float dt) override;
		void Render() const override{};

		bool IsPurple() const { return m_IsPurple; }
	private:
		id m_OldId;
		id m_NewId;
		position m_Position;
		float m_Size;
		bool m_IsPurple;
		EnemyBehaviour* m_pBehaviour = nullptr;
		bool m_IsRevertingTiles;
		dae::RenderComponent* m_pRenderComp;
	};
}


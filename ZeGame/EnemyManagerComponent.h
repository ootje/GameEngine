#pragma once
#include <BaseComponent.h>
#include <vector>

#include "Helpers.h"
#include "Scene.h"

namespace qbert
{
	class EnemyComponent;

	class EnemyManagerComponent final : public dae::BaseComponent
	{
	public:
		EnemyManagerComponent(int gameMode, dae::Scene& scene);
		~EnemyManagerComponent();

		void Update(float dt) override;
		void Render() const override{};

		bool HandleCollision(position pos, float width, float height);
		void Reset();
	
	private:
		std::vector<EnemyComponent*> m_Enemies;
		bool m_InactiveEnemy;
		float m_Duration;
		float m_Elapsed;
	};
}


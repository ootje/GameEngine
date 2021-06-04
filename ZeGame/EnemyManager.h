#pragma once
#include "Singleton.h"


namespace qbert
{
	class EnemyManager final : public dae::Singleton<EnemyManager>
	{
	public:
		void LoadEnemies();


	private:
		friend class Singleton<EnemyManager>;
		EnemyManager() = default;
	};
}


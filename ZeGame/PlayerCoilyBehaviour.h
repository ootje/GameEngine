#pragma once
#include "EnemyBehaviour.h"

namespace qbert
{
	class PlayerCoilyBehaviour final : public EnemyBehaviour
	{
	public:
		PlayerCoilyBehaviour() = default;
		~PlayerCoilyBehaviour(){};
		id CalculateNextMove(id currentId) override { return currentId; };
		int EventOnDeath() override { return -1; };
	};
}


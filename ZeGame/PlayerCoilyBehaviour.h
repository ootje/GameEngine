#pragma once
#include "EnemyBehaviour.h"

namespace qbert
{
	class PlayerCoilyBehaviour final : public EnemyBehaviour
	{
	public:
		PlayerCoilyBehaviour() = default;
		~PlayerCoilyBehaviour();
		id CalculateNextMove(id currentId) const override;
	};
}

